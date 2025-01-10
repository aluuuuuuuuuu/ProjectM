#include "CharactorSelectManager.h"
#include "SelectFinger.h"
#include "CharactorCard.h"
#include "Vec2.h"
#include "Input.h"

CharactorSelectManager::CharactorSelectManager(PlayerData& plData) :
	_plData(plData),
	_selectFinishFlag(false),
	_pushStart(false)
{
	// 指のインスタンスを人数分作成する
	for (int i = 0; i <= _plData.playerNum; i++) {
		_pFinger[i] = std::make_shared<SelectFinger>(i);
	}

	// カードのインスタンスをキャラクター分作成する
	for (int i = 0; i < 4; i++) {
		_pCard[i] = std::make_shared<CharactorCard>(i);
	}
}

CharactorSelectManager::~CharactorSelectManager()
{
}

void CharactorSelectManager::Update()
{

	// 全指の更新処理
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Update();
	}

	// 全カードの描画
	for (auto& card : _pCard) {
		card->Draw();
	}

	// 指とカードの判定をとる
	FingerFunction();

	// 全指が選択し終わったか判定する
	_selectFinishFlag = true;
	for (int num = 0; num <= _plData.playerNum; num++) {
		if (!_pFinger[num]->IsSelected()) {
			_selectFinishFlag = false;
			break;
		}
	}

	// 選び終わった後に仮表示している円の上でAボタンを押したらゲームが開始される
	if (_selectFinishFlag && Input::GetInstance().IsTrigger(INPUT_A,INPUT_PAD_1)) {
		if ((_pFinger[0]->GetPos() - Vec2{ 600,600 }).Length() <= 200) {
			_pushStart = true;
		}
	}
}

void CharactorSelectManager::Draw() const
{
	// 全カードの描画
	for (auto& card : _pCard) {
		card->Draw();
	}

	// 全指の描画
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}

	// 選択し終わっていたら何かを表示する
	if (_selectFinishFlag) {
		DrawCircle(600, 600, 200, 0xff0000);
	}
}

bool CharactorSelectManager::GetStart() const
{
	return _pushStart;
}

void CharactorSelectManager::CreateData()
{
	for (int num = 0; num <= _plData.playerNum; num++) {
		_plData.charactor[num] = _pFinger[num]->GetSelectChara();
	}
}

void CharactorSelectManager::FingerFunction()
{
	for (int num = 0; num <= _plData.playerNum; num++) {

		// Aボタンを押したときの処理
		if (_pFinger[num]->IsPushButton(INPUT_A)) {
			for (auto& card : _pCard) {
				// まだ選択しておらず、選択されていないカードと重なっていたら選択する
				if (IsFingerOnCard(_pFinger[num], card) && !card->GetSelectFlag() && !_pFinger[num]->IsSelected()) {
					card->SelectCharactor(_pFinger[num]->GetPadNum());
					_pFinger[num]->SetSelectFlag(true);
					_pFinger[num]->SetSelectChara(card->GetCharactorNum());
				}
			}
		}

		// Bボタンを押したときの処理
		if (_pFinger[num]->IsPushButton(INPUT_B)) {
			for (auto& card : _pCard) {
				// 選択していて、対象の指が選択したカードと重なっていたら選択解除する
				if (card->GetSelectFlag(num)) {
					_pFinger[num]->SetSelectFlag(false);
					_pCard[_pFinger[num]->GetSelectChara() - 1]->RejectCharactor(num);
				}
			}
		}
	}
}

bool CharactorSelectManager::IsFingerOnCard(std::shared_ptr<SelectFinger>& fing, std::shared_ptr<CharactorCard>& card)
{
	// それぞれの座標を取得
	Vec2 fingPos = fing->GetPos();
	Vec2 cardPos = Vec2{ card->GetPos().x + 10.0f,card->GetPos().y + 10.0f };

	// fingerがカードの上にあるか判定
	if (fingPos.x >= cardPos.x &&
		fingPos.x <= cardPos.x + card->GetConstantInt("CARD_SIZE_WIDTH") &&
		fingPos.y >= cardPos.y &&
		fingPos.y <= cardPos.y + card->GetConstantInt("CARD_SIZE_HEIGHT")) {

		return true;
	}
	return false;
}
