#pragma once

// �N���X���V���O���g���p�^�[���Ŏ�������e���v���[�g
template<typename T>
class Singleton 
{
public:

    // �C���X�^���X��񋟂���
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    
    // �C���X�^���X�̃R�s�[�𐧌�����
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    // �R���X�g���N�^�ƃf�X�g���N�^�̊O����̃A�N�Z�X�𐧌�����
    Singleton() {}
    ~Singleton() {}
};