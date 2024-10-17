#include "PlayerCamera.h"
#include "DxLib.h"
#include "Input.h"

PlayerCamera::PlayerCamera(Vec3 pos)
{
	// �O���t�@�C������萔���擾����
	ReadCSV("data/constant/PlayerCamera.csv");

	// �J�����̃j�A�t�@�[�̐ݒ�
	SetCameraNearFar(GetConstantFloat("CAMERA_NEAR"), GetConstantFloat("CAMERA_FAR"));

	// �����ʒu�ɐݒ肷��
	Position = Vec3{ pos.x + GetConstantFloat("CAMERA_BASE_POS_X"),
					 pos.y + GetConstantFloat("CAMERA_BASE_POS_Y"),
					 pos.z + GetConstantFloat("CAMERA_BASE_POS_Z"), };
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(Vec3 pos)
{
	// �^�[�Q�b�g�̐ݒ�
	Vec3 target;
	target = Vec3(pos.x, pos.y + GetConstantFloat("CAMERA_MARGIN_Y"), pos.z);

	// ���W�̐ݒ�

	SetCameraPositionAndTarget_UpVecY(Rotate(pos).VGet(), target.VGet());
}

Vec3 PlayerCamera::Rotate(Vec3 pos)
{
	// �C���v�b�g�̃C���X�^���X���擾
	auto& input = Input::GetInstance();

	// �E�X�e�B�b�N�ŉ�]
	if (input.GetStickVectorLength(INPUT_RIGHT_STICK, INPUT_PAD_1) > GetConstantFloat("STICK_INVALID_VALUE")) {

		// �X�e�B�b�N���X���������̉�]�̒l�𑝌�������
		if (input.GetStickVector(INPUT_RIGHT_STICK, INPUT_PAD_1).x != 0) {
			Angle.y += GetConstantFloat("CAMERA_ANGLE_VARIATION") * (input.GetStickThumbX(INPUT_RIGHT_STICK, INPUT_PAD_1));
		}
		if (input.GetStickVector(INPUT_RIGHT_STICK, INPUT_PAD_1).z != 0) {
			Angle.z += GetConstantFloat("CAMERA_ANGLE_VARIATION") * (input.GetStickThumbY(INPUT_RIGHT_STICK, INPUT_PAD_1));
		}

		// ���W�A���p�𐳋K������
		Angle.y = fmodf(Angle.y, static_cast<float>(DX_TWO_PI));
		if (Angle.y < 0.0f) Angle.y += static_cast<float>(DX_TWO_PI);
	}

	// �ő�l�ƍŒ�l�𒲐�����
	if (Angle.z <= -GetConstantFloat("CAMERA_ANGLE_RANGE")) {
		Angle.z = -GetConstantFloat("CAMERA_ANGLE_RANGE");
	}
	else if (Angle.z >= GetConstantFloat("CAMERA_ANGLE_RANGE")) {
		Angle.z = GetConstantFloat("CAMERA_ANGLE_RANGE");
	}

	// ��ƂȂ�J�����̍��W
	Vec3 basePos = VGet(GetConstantFloat("CAMERA_BASE_POS_X"),GetConstantFloat("CAMERA_BASE_POS_Y"), GetConstantFloat("CAMERA_BASE_POS_Z"));

	// �J�������W�̓v���C���[���W����ϊ��������W�𑫂����Ƃ���
	return VAdd(VGet(pos.x, pos.y, pos.z), RotatePos(basePos).VGet());
}

Vec3 PlayerCamera::RotatePos(Vec3 pos)
{
	// ��]�s����쐬
	MATRIX rotMtxX, rotMtxZ;
	rotMtxX = MGetRotY(Angle.y);
	rotMtxZ = MGetRotX(Angle.z);

	// ����W���s��ŕϊ�
	pos = VTransform(pos.VGet(), rotMtxZ);
	pos = VTransform(pos.VGet(), rotMtxX);

	return pos;
}
