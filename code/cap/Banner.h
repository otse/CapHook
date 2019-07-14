#pragma once

#include <d3d11.h>

namespace cap
{
	extern bool ChrisOrSebastian;

	extern ID3D11ShaderResourceView* TextureView_;
	extern ID3D11Texture2D *texture2d_;

	void CAPUPLOADBANNER();

	void CAPDRAWBANNER();
	
	void CAPSTOREVARS(
		IDXGISwapChain *,
		ID3D11Device *,
		ID3D11DeviceContext *,
		ID3D11RenderTargetView *);

	struct CAPVARS
	{
		IDXGISwapChain *swapchain;
		ID3D11Device *device;
		ID3D11DeviceContext *context;
		ID3D11RenderTargetView *rtv;
	};
}