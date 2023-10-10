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

	void PreDraw();

	void PostDraw();
private:
	/// <summary>
	/// Initialize
	/// </summary>
	void InitializeDXGIFactory();

	void InitializeAdapter();

	void InitializeDebugLayer();
	
	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapChain();

	void InitializeRenderTargetView();

	void InitializeDepthBuffer();

	void InitializeFence();

	/// <summary>
	/// PreDraw
	/// </summary>

	void Barrier();

	void RenderTargetView();

	/// <summary>
	/// PostDraw
	/// </summary>
	
	void ScreenDisplay();

	//
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);

	ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

private:
	WindowsAPI* winAPI_ = nullptr;
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;

	//スワップチェーン生成
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain;

	//ディスクリプターヒープの生成
	ID3D12DescriptorHeap* rtvDescriptorHeap;
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc;
	ID3D12DescriptorHeap* srvDescriptorHeap;

	ID3D12Resource* swapChainResource[2];

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc;

	//ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;

	//RTVを２つ作るのでディスクリプタ２つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle[2];


	//Direct3D関連
	IDXGIAdapter4* useAdapter_;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap_;
	//バックバッファ
	//std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers_;
	UINT backBufferIndex;

	D3D12_RESOURCE_BARRIER barrier;
};

