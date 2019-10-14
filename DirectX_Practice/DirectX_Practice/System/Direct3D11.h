#pragma once

#include "DirectXIncLib.h"

//�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
struct SimpleShaderConstantBuffer0 {
    D3DXMATRIX mW;//���[���h�s��
    D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
    D3DXVECTOR4 mLightDir;//���C�g����
    D3DXVECTOR4 mEye;//�J�����ʒu	
};

struct SimpleShaderConstantBuffer1 {
    D3DXVECTOR4 mAmbient;//�A���r�G���g��
    D3DXVECTOR4 mDiffuse;//�f�B�t���[�Y�F
    D3DXVECTOR4 mSpecular;//���ʔ���
    D3DXVECTOR4 mTexture;//�e�N�X�`���[���\���Ă��郁�b�V�����ǂ����̃t���O
};

struct D3DInit {
    HWND mHwnd;
};

class Direct3D11 {
public:
    Direct3D11();
    ~Direct3D11();
    HRESULT init(D3DInit*);
    void clear();
    HRESULT present();

    static ID3D11Device* mDevice;
    static ID3D11DeviceContext* mDeviceContext;
    static ID3D11RasterizerState* mRasterizerState; //�O�ʗp
    static ID3D11RasterizerState* mRasterizerStateBack; //�w�ʗp

private:
    HWND mHwnd;
    IDXGISwapChain* mSwapChain;
    ID3D11RenderTargetView* mRenderTargetView;
    ID3D11DepthStencilView* mDepthStencilView;
    ID3D11Texture2D* mDepthStencil;
    ID3D11DepthStencilState* mDepthStencilState;
};

