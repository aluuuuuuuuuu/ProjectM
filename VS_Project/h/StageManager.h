#pragma once
class StageManager
{
public:
	StageManager();
	virtual ~StageManager();

	/// <summary>
	/// �X�e�[�W��`�悷��
	/// </summary>
	void DrawStage() const;

    /// <summary>
    /// �X�e�[�W�̔z��̒��g���擾����
    /// </summary>
    /// <param name="a">�z���x�v�f</param>
    /// <param name="b">�z���y�v�f</param>
    /// <param name="c">�z���z�v�f</param>
    /// <returns>�z��̗v�f</returns>
    int GetStageInfo(int a, int b, int c);

    /// <summary>
    /// �w�肳�ꂽ�{�b�N�X��0������
    /// </summary>
    /// <param name="x">�}�X�̗v�f��x</param>
    /// <param name="y">�}�X�̗v�f��y</param>
    /// <param name="z">�}�X�̗v�f��z</param>
    void DeleteBox(int x, int y, int z);

private:



    int _stage[10][2][10];
};

