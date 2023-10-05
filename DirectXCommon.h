#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WindowsAPI.h"

class DirectXCommon
{
public:
	void Initialize(WindowsAPI* winAPI);

	void Update();
private:
	void InitializeAdapter();
	
	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapChain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

private:
	WindowsAPI* winAPI_ = nullptr;
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	//Direct3D関連
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	//バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
};

