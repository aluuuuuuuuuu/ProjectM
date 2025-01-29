#include "PlayerManager.h"
#include "Application.h"
#include "DxLib.h"
#include "CollisionManager.h"
#include "Player.h"
#include "PlayerUi.h"

PlayerManager::PlayerManager(std::shared_ptr<StageManager>& stageManager, std::shared_ptr<BulletManager>& bullet, PlayerData& data) :
	_playerData(data),
	_bulletManager(bullet)
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/Player.csv");

	// ���f���̃��[�h
	_modelHandle[0] = MV1LoadModel("data/model/Player11.mv1");
	_modelHandle[1] = MV1LoadModel("data/model/Player2.mv1");
	_modelHandle[2] = MV1LoadModel("data/model/Player3.mv1");
	_modelHandle[3] = MV1LoadModel("data/model/Player4.mv1");

	// �e�C���X�^���X�̍쐬
	{
		// �v���C���[�C���X�^���X�̍쐬
		for (int num = 0; num <= _playerData.playerNum; num++) {
			
			_pPlayer.push_back(std::make_shared<Player>(bullet, *this, num, _bulletData[num]));

			switch (num)
			{
			case 0:
				_pPlayer[num]->Position = Vec3{ 0.0f,0.0f,0.0f };
				
				// �v���C���[�̊p�x�����W�A����-45�x�ɐݒ�
				_pPlayer[num]->Angle.y = DX_PI_F / -4;
				break;
			case 1:
				_pPlayer[num]->Position = Vec3{ 180.0f,0.0f,180.0f };

				// �v���C���[�̊p�x�����W�A����-180�x�ɐݒ�
				_pPlayer[num]->Angle.y = DX_PI_F / -4 * 5;
				break;
			case 2:
				_pPlayer[num]->Position = Vec3{ 0.0f,0.0f,180.0f };

				// �v���C���[�̊p�x�����W�A����-135�x�ɐݒ�
				_pPlayer[num]->Angle.y = DX_PI_F / -4 * 3;
				break;
			case 3:
				_pPlayer[num]->Position = Vec3{ 180.0f,0.0f,0.0f };

				// �v���C���[�̊p�x�����W�A����-90�x�ɐݒ�
				_pPlayer[num]->Angle.y = DX_PI_F / -4 * 7;
				break;
			default:
				break;
			}
		}

		// �R���W�����}�l�[�W���[�̍쐬
		_pCollision = std::make_shared<CollisionManager>(stageManager);

		// �v���C���[UI�C���X�^���X�̍쐬
		_pUi = std::make_shared<PlayerUi>(_playerData.playerNum);
	}

	// �E�B���h�E�̕��ƍ������擾
	_windowHeight = Application::GetInstance().GetConstantInt("SCREEN_HEIGHT");
	_windowWidth = Application::GetInstance().GetConstantInt("SCREEN_WIDTH");

	// �`��͈͂ƃJ�����Z���^�[�̍쐬
	int num = 0;
	for (auto& pl : _pPlayer) {
		_drawArea[num] = CreateDrawArea(num, _windowWidth, _windowHeight);		// �`��͈�
		_cameraSenter[num] = CreateScreenCenter(num, _windowWidth, _windowHeight);	// �J�����̃Z���^�[
		num++;
	}
}

PlayerManager::~PlayerManager()
{
	// ���f���̃f���[�g
	for (int num = 0; num < GetConstantInt("MAX_NUM"); num++) {
		MV1DeleteModel(_modelHandle[num]);
	}
}

void PlayerManager::Update()
{
	// �v���C���[�̈ړ��Ȃ�
	for (auto& pl : _pPlayer) {
		pl->Control();
	}

	ColResult result = _pCollision->PlayerCollision(_pPlayer);

	// �v���C���[�̓����蔻��
	for (int i = 0; i < _pPlayer.size(); i++) {
		_pPlayer[i]->Position += result.vec[i];
	}

	// �v���C���[�̍X�V
	for (auto& pl : _pPlayer) {

		// �X�V����
		pl->Update();

		// ������
		if (pl->Position.y <= GetConstantFloat("DEAD_LINE")) {
			pl->KillPlayer();
		}
	}
}

void PlayerManager::Draw(int num) const
{
	// �v���C���[�̕`��
	for (auto& pl : _pPlayer) {
		pl->Draw();
	}

	// UI�̕`��
	_pUi->Draw(Vec2{ _cameraSenter[num].a ,_cameraSenter[num].b },_bulletData[num]);

}

VECTOR4 PlayerManager::GetArea(int num) const
{
	return _drawArea[num];
}

VECTOR2 PlayerManager::GetCenter(int num) const
{
	return _cameraSenter[num];
}

int PlayerManager::GetPlayerNum() const
{
	return static_cast<int>(_pPlayer.size());
}

int PlayerManager::GetModelHandle(int num) const
{
	// �v���C���[�i���o�[�ɑΉ��������f���n���h����Ԃ�
	return MV1DuplicateModel(_modelHandle[_playerData.character[num]]);
}

void PlayerManager::CameraSet(int num) const
{
	// �J�����̃Z�b�g
	_pPlayer[num]->CameraSet();
}

int PlayerManager::GetAreAlivePlayerNum() const
{
	// �����Ă���v���C���[�𐔂���
	int num = 0;
	for (auto& pl : _pPlayer) {
		if (!pl->GetDeadFlag()) num++;
	}
	return num;
}

PlayerData PlayerManager::GetPlayerData() const
{
	return _playerData;
}

void PlayerManager::SetWinner()
{
	for (auto& pl : _pPlayer) {
		if (!pl->GetDeadFlag()) {
			_playerData.winner = _playerData.character[pl->GetPlayerNum()];
		}
	}
}

void PlayerManager::AddAi()
{
	// AI�̒ǉ�
	_playerData.playerNum++;
	_playerData.character[1] = rand() % 3;
	_pPlayer.push_back(std::make_shared<Player>(_bulletManager, *this, _bulletData[_playerData.playerNum]));
	_pPlayer[_playerData.playerNum]->Position = Vec3{ 180.0f,0.0f,180.0f };
	_pPlayer[_playerData.playerNum]->Angle.y = DX_PI_F / -4 * 5;
}

Vec3 PlayerManager::GetPlayerPos() const
{
	return _pPlayer[0]->Position;
}

bool PlayerManager::GetAiFlag()
{
	return _playerData.aiFlag;
}

void PlayerManager::DeleteAi()
{
	_playerData.playerNum--;
	_playerData.character[1] = -1;
}

VECTOR4 PlayerManager::CreateDrawArea(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int halfWidth = scWidth / 2;
	int halfHeight = scHeight / 2;

	// �v���C���[�̑����ŏ�����؂�ւ���
	switch (size)
	{
	case 1:
		return VECTOR4{ 0,0,scWidth,scHeight };
		break;
	case 2:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth , scHeight };
		}
		else {
			return VECTOR4{ halfWidth, 0,scWidth ,
							scHeight };
		}
		break;

	case 3:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		break;

	case 4:
		if (num == 0) {
			return VECTOR4{ 0,0,halfWidth ,halfHeight };
		}
		else if (num == 1) {
			return VECTOR4{ halfWidth ,0,scWidth ,
							halfHeight };
		}
		else if (num == 2) {
			return VECTOR4{ 0,halfHeight ,halfWidth ,
							scHeight };
		}
		else {
			return VECTOR4{ halfWidth ,halfHeight ,
							scWidth,scHeight };
		}
		break;
	default:
		return VECTOR4{};
		break;
	}
}

VECTOR2 PlayerManager::CreateScreenCenter(int num, int scWidth, int scHeight)
{
	int size = static_cast<int>(_pPlayer.size());

	int width;
	int height;

	switch (size)
	{
	case 1:
		return VECTOR2{ scWidth / 2,scHeight / 2 };
		break;

	case 2:

		width = scWidth / 4;
		height = scHeight / 2;

		if (num == 0) {
			return VECTOR2{ width , height };
		}
		else {
			return VECTOR2{ width * 3, height };
		}
		break;

	case 3:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else {
			return VECTOR2{ width, height * 3 };
		}
		break;

	case 4:

		width = scWidth / 4;
		height = scHeight / 4;

		if (num == 0) {
			return VECTOR2{ width ,height };
		}
		else if (num == 1) {
			return  VECTOR2{ width * 3, height };
		}
		else if (num == 2) {
			return VECTOR2{ width, height * 3 };
		}
		else {
			return VECTOR2{ width * 3, height * 3 };
		}
		break;
	default:
		return VECTOR2{};
		break;
	}
}
