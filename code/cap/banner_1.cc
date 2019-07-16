#pragma once

#include "cap_1.h"

#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <string>
#include <algorithm>

#include <imgui.h>

#include <comdef.h>

#include <Utility/PathUtils.h>

namespace cap
{
bool ChrisOrSebastian = false;

CAPVARS vars;

void CAPSTOREVARS(
	IDXGISwapChain *swapchain,
	ID3D11Device *device,
	ID3D11DeviceContext *context,
	ID3D11RenderTargetView *rtv)
{
	std::puts("Stored id3d for cap");

	vars.swapchain = swapchain;
	vars.device = device;
	vars.context = context;
	vars.rtv = rtv;
}

void CAPDRAWBANNER()
{
	static bool window = true;

	auto flags = ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar |
				 ImGuiWindowFlags_AlwaysAutoResize |
				 ImGuiWindowFlags_NoSavedSettings |
				 ImGuiWindowFlags_NoFocusOnAppearing |
				 ImGuiWindowFlags_NoResize |
				 ImGuiWindowFlags_NoScrollbar |
				 ImGuiWindowFlags_NoNav;

	ImGuiIO &io = ImGui::GetIO();

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, ImVec2(0, 0));

	ImGui::SetNextWindowBgAlpha(0.0f);

	ImVec2 window_pos = ImVec2(io.DisplaySize.x - 50, 50);
	ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

	// The Window

	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(255, 255, 255, 0));

	ImGui::Begin("Banner", &window, flags);

	// The Banners
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));

	ImGui::BeginChild("Banners", ImVec2(900, 500));

	size_t num_banners = banners_.size();

	//ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 20.f);

	for (auto &pair : banners_)
	{
		Banner &banner = pair.second;
		ImGui::Image((void *)banner.view, ImVec2(900, 500)); ImGui::SameLine();
	}

	float scroll_x = ImGui::GetScrollX();
	float scroll_max_x = ImGui::GetScrollMaxX();

	ImGui::PopStyleVar(2);

	ImGui::EndChild();
	
	float max = 900.0f * (num_banners - 1);

	static float x = 0;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.f,12.f));
	ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 80.f);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1, 1, 1, 0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(1, 1, 1,0));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(1, 1, 1, 0));

	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(130/255.f, 0, 130/255.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(1, 1, 1, 1));

	ImGui::PushItemWidth(900);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 0));

	bool use = ImGui::SliderFloat("##water", &x, 0.0f, max);

	ImGui::PopStyleColor(1);

	ImGui::PopItemWidth();

	ImGui::PopStyleColor(5);
	ImGui::PopStyleVar(2);

	const float w = 900.f;
	const float ha = w / 2.f;

	const float shift = 1.f / 60.f * 400.f;

	/*auto EaseInOutQuad = ([](float t) {
		return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
	});*/

	if (!use)
	{
		int i = 0;
		for (; i < num_banners; i++)
		{
			float b = i * w;
			if (x < b - ha || x > b + ha)
				continue;
			float force = shift;
			if (x < b) {
				//force += (x - b) / 100.f;
				x += force;
				if (x > b)
					x = b;
			}
			else {
				//force += (x - b) / 100.f;
				x -= force;
				if (x < b)
					x = b;
			}
			//if (x < b || x > b)
				//x = b;
		}
		std::clamp(x, 0.f, max);
	}

	// Go back to the Hulk
	ImGui::BeginChild("Banners");
	ImGui::SetScrollX((int)x);
	ImGui::EndChild();

	//ImGui::Separator();

	//ImGui::BeginChild("Radios");

	//ImGui::Columns(2);

	//ImGui::NextColumn();
	//ImGui::NextColumn();

	/*static int e = 0;
	ImGui::RadioButton("#a", &e, 0); ImGui::SameLine();
	ImGui::RadioButton("#b", &e, 1); ImGui::SameLine();
	ImGui::RadioButton("#c", &e, 2); ImGui::SameLine();
	ImGui::RadioButton("#d", &e, 3);

	//ImGui::EndChild();

	switch(e)
	{
		case 0: which = L"pink winter soldier"; break;
		case 1: which = L"pink captain america"; break;
		default: which = L"pink captain america";
		//case 2: which = L"pink winter soldier"; break;
	}*/

	ImGui::End();

	ImGui::PopStyleColor(1);

	//ImGui::PopStyleVar(1);
}

/*
void BLOO()
{
	const wchar_t *swap = L"shieldmod\\chris or seb";

	auto chris_or_seb = Utility::MakeAbsolutePathW(swap).c_str();

	if (INVALID_FILE_ATTRIBUTES != GetFileAttributesW(chris_or_seb))
	{
		ChrisOrSebastian = true;
		DeleteFileW(chris_or_seb);
	}
	else
	{
		ChrisOrSebastian = false;
		CreateFileW(chris_or_seb, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	}
}*/

std::map<const std::wstring, Banner> banners_;

/// supports reuploading banner art
void CAPUPLOADBANNER(const wchar_t *pink)
{
	int width = 900;
	int height = 500;

	if (banners_.find(pink) == banners_.end())
	{
		banners_.emplace(pink, Banner());
	}
	Banner &banner = banners_.at(pink);

	auto base = Utility::MakeAbsolutePathW(L"shieldmod\\");
		
	auto art = (base + pink).c_str();

	// ugly
	FILE *fh = nullptr;
	_wfopen_s(&fh, art, L"rb");

	fseek(fh, 0, SEEK_END);

	auto length = ftell(fh);

	fseek(fh, 0, SEEK_SET);

	unsigned char *data = new unsigned char[length];
	data[length] = 0;
	fread(data, 1, length, fh);
	fclose(fh);
	// ugly

	unsigned char *pixels = data;

	int h = 0;
	for (; h < height; h++)
	{
		int w = 0;
		for (; w < width; w++)
		{
			//pixels += data.;
		}
	}

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;

	HRESULT hr = vars.device->CreateTexture2D(&desc, &subResource, &banner.texture);

	if (FAILED(hr))
	{
		std::cout << "capuploadbanner texture2d hresult " << std::hex << hr << std::endl;
		return;
	}

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	hr = vars.device->CreateShaderResourceView(banner.texture, &srvDesc, &banner.view);

	if (FAILED(hr))
	{
		std::cout << "capuploadbanner textureview hresult " << std::hex << hr << std::endl;
		return;
	}
}

} // namespace cap