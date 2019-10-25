#include "Score.h"
#include "Sprite.h"

Score::Score():
	mScore(123),
    mPosition(Vector2(1000.0f,0.0f)){
	mSprite = new Sprite(this, "number.png", Vector2(500.f, 100.f), 0.1f);
	mSprite->setPosition(mPosition);
}

Score::~Score(){
}

void Score::update(){

	drawScore();
}

void Score::drawScore()
{
	// �}�C�i�X�̐���0
	if (mScore < 0) {
		mScore = 0;
	}

	int width = 32; // �摜����

	//�����v�Z(�{����=1)
	int digit = 0;
	for (int i = mScore; i >= 10; i /= 10) {
		digit++;
	}

	mSprite->setPosition(Vector2(mPosition.x - width * digit, mPosition.y));
	//mSprite->setPosition(Vector2(mSprite->getPosition().x - width * digit, mSprite->getPosition().y));
	//position.X -= width * digit;

	// �����𕶎��񉻂��A1���������o��
	for (auto n : std::to_string(mScore)) {
		// �����̃e�N�X�`��������1�ɂ���32����64
		// �����ƕ����������Z���A�����l���擾���Ă���
		float num = (n - '0') * width;
		num /= mSprite->getSize().x;
		//(n -'0') * width, 0, width, mSprite->getSize().y)
		mSprite->setUV(num, 0, width / mSprite->getSize().x, 1);
		mSprite->draw();

		// 1�����`�悵����1�����E�ɂ��炷
		mSprite->setPosition(Vector2(mSprite->getPosition().x + width, mSprite->getPosition().y));
		//position.X += width;
	}
}

void Score::addScore(int score){
	mScore += score;
}
