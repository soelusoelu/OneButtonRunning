#include "Score.h"
#include "Sprite.h"

Score::Score() :
    mScore(0),
    mPosition(Vector2(1000.0f, 0.0f)) {
    mSprite = std::make_unique<Sprite>("number.png", Vector2(512.f, 64.f), 0.1f);
    mSprite->setPosition(mPosition);
}

Score::~Score() = default;

void Score::update() {
    mScore++;
    drawScore(mScore / 60);
}

void Score::drawScore(int score) {
    // �}�C�i�X�̐���0
    if (score < 0) {
        score = 0;
    }

    int width = 32; // �摜����

    //�����v�Z(�{����=1)
    int digit = 0;
    for (int i = score; i >= 10; i /= 10) {
        digit++;
    }

    mSprite->setPosition(Vector2(mPosition.x - width * digit, mPosition.y));

    // �����𕶎��񉻂��A1���������o��
    for (auto n : std::to_string(score)) {
        // �����̃e�N�X�`��������1�ɂ���32����64
        // �����ƕ����������Z���A�����l���擾���Ă���
        float num = (n - '0') * width;
        num /= mSprite->getSize().x;
        mSprite->setUV(num, 0, width / mSprite->getSize().x, 1);
        mSprite->draw();

        auto pos = mSprite->getPosition();
        // 1�����`�悵����1�����E�ɂ��炷
        mSprite->setPosition(Vector2(mSprite->getPosition().x + width, mSprite->getPosition().y));
    }
}

void Score::addScore(int score) {
    mScore += score;
}
