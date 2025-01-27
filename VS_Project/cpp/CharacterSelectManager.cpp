#include "CharacterSelectManager.h"
#include "SelectFinger.h"
#include "CharacterCard.h"
#include "Input.h"
#include "SoundManager.h"

CharacterSelectManager::CharacterSelectManager(PlayerData& plData) :
	_plData(plData),
	_selectFinishFlag(false),
	_pushStart(false),
	_returnFlag(false),
	_startButtonHandle(0),
	_viewStartButtonFlag(false)
{
	// 指のインスタンスを人数分作成する
	for (int i = 0; i <= _plData.playerNum; i++) {
		_pFinger[i] = std::make_shared<SelectFinger>(i);
	}

	// カードのインスタンスをキャラクター分作成する
	for (int i = 0; i < 4; i++) {
		_pCard[i] = std::make_shared<CharacterCard>(i);
	}

	// スタート画像のロード
	_startButtonHandle = LoadGraph("data/image/ReadyFight.png");
	_startButtonPos = Vec2{ 960,1500 };
}

CharacterSelectManager::~CharacterSelectManager()
{
	DeleteGraph(_startButtonHandle);
}

void CharacterSelectManager::UpdatePl()
{
	// 全指の更新処理
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->UpdatePl();
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

	// スタートボタンをスライドイン・アウトさせる
	if (_selectFinishFlag) {
		_viewStartButtonFlag = true;
		if (_startButtonPos.y > 900.0f) {
			_startButtonPos.y -= 45.0f;
			if (_startButtonPos.y < 900.0f) {
				_startButtonPos.y = 900.0f;
			}
		}
	}
	else {
		if (1500 >= _startButtonPos.y) {
			_startButtonPos.y += 45.0f;
		}
		else {
			_viewStartButtonFlag = false;
		}
	}
}

void CharacterSelectManager::Draw() const
{
	// 全カードの描画
	for (auto& card : _pCard) {
		card->Draw();
	}

	// 選択し終わっていたらスタートボタンを表示する
	if (_viewStartButtonFlag) {
		DrawRotaGraph(_startButtonPos.intX(), _startButtonPos.intY(), 1.0, 0.0, _startButtonHandle, true);
	}

	// 全指の描画
	for (int num = 0; num <= _plData.playerNum; num++) {
		_pFinger[num]->Draw();
	}
}

bool CharacterSelectManager::GetStart() const
{
	return _pushStart;
}

void CharacterSelectManager::CreateData()
{
	for (int num = 0; num <= _plData.playerNum; num++) {
		_plData.character[num] = _pFinger[num]->GetSelectChara();
	}
}

bool CharacterSelectManager::GetReturnFlag()
{
	return _returnFlag;
}

void CharacterSelectManager::FingerFunction()
{
	for (int num = 0; num <= _plData.playerNum; num++) {

		// Aボタンを押したときの処理
		if (_pFinger[num]->IsPushButton(INPUT_A)) {
			for (auto& card : _pCard) {
				// まだ選択しておらず、選択されていないカードと重なっていたら選択する
				if (IsFingerOnCard(_pFinger[num], card) && !card->GetSelectFlag() && !_pFinger[num]->IsSelected()) {
					card->SelectCharacter(_pFinger[num]->GetPadNum());
					_pFinger[num]->SetSelectFlag(true);
					_pFinger[num]->SetSelectChara(card->GetCharacterNum());

					// キャラ選択音を鳴らす
					SoundManager::GetInstance().RingSE(SE_CHARA_SELECT);
				}
			}

			// 選択終了していたときに指がスタートボタンに重なっていたらゲームスタート処理を行う
			if (_selectFinishFlag) {
				if (_pFinger[num]->GetPos().x > _startButtonPos.x - 515 && _pFinger[num]->GetPos().x < _startButtonPos.x + 515 &&
					_pFinger[num]->GetPos().y > _startButtonPos.y - 125 && _pFinger[num]->GetPos().y < _startButtonPos.y + 250) {
					_pushStart = true;

					// ゲームスタート音を鳴らす
					SoundManager::GetInstance().RingSE(SE_GAME_START);
				}
			}
		}

		// Bボタンを押したときの処理
		if (_pFinger[num]->IsPushButton(INPUT_B)) {
			// 選択していたら選択を解除する
			if (_pFinger[num]->IsSelected()) {
				_pCard[_pFinger[num]->GetSelectChara()]->RejectCharacter(num);
				_pFinger[num]->SetSelectFlag(false);

				// キャンセル音を鳴らす
				SoundManager::GetInstance().RingSE(SE_CHARA_CANCEL);
			}
			// 選択していなかったら人数選択に戻る
			else {
				_returnFlag = true;
			}

		}
	}
}

bool CharacterSelectManager::IsFingerOnCard(std::shared_ptr<SelectFinger>& fing, std::shared_ptr<CharacterCard>& card)
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
