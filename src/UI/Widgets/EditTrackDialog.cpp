//==============================================================================
// UI/Widgets/EditTrackDialog.cpp
//==============================================================================

#include "EditTrackDialog.h"
#include <imgui.h>
#include <cstring>

namespace moosic
{

void EditTrackDialog::Open(const MusicTrack* track)
{
    if (!track) return;
    
    m_editingTrack = track;
    m_shouldOpen = true;
    m_isOpen = true;
    
    strncpy(m_titleBuffer, track->GetTitle().c_str(), sizeof(m_titleBuffer) - 1);
    m_titleBuffer[sizeof(m_titleBuffer) - 1] = '\0';
    
    strncpy(m_artistBuffer, track->GetArtist().c_str(), sizeof(m_artistBuffer) - 1);
    m_artistBuffer[sizeof(m_artistBuffer) - 1] = '\0';
    
    strncpy(m_albumBuffer, track->GetAlbum().c_str(), sizeof(m_albumBuffer) - 1);
    m_albumBuffer[sizeof(m_albumBuffer) - 1] = '\0';
}

void EditTrackDialog::Close()
{
    m_isOpen = false;
    m_editingTrack = nullptr;
}

void EditTrackDialog::Draw()
{
    if (!m_isOpen) return;
    
    if (m_shouldOpen)
    {
        ImGui::OpenPopup("EditTrackDialog");
        m_shouldOpen = false;
    }
    
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(420, 230), ImGuiCond_Appearing);
    
    if (ImGui::BeginPopupModal("EditTrackDialog", nullptr, ImGuiWindowFlags_NoResize))
    {
        ImGui::TextColored(m_theme.BrandText, "Edit Track Info");
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.FrameBg);
        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
        
        float labelWidth = 60.0f;
        float spacing = 10.0f;
        
        // Title
        ImGui::Text("Title:");
        ImGui::SameLine(labelWidth + spacing);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        if (ImGui::IsWindowAppearing())
            ImGui::SetKeyboardFocusHere();
        ImGui::InputText("##EditTitle", m_titleBuffer, sizeof(m_titleBuffer));
        
        ImGui::Spacing();
        
        // Artist
        ImGui::Text("Artist:");
        ImGui::SameLine(labelWidth + spacing);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputText("##EditArtist", m_artistBuffer, sizeof(m_artistBuffer));
        
        ImGui::Spacing();
        
        // Album
        ImGui::Text("Album:");
        ImGui::SameLine(labelWidth + spacing);
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputText("##EditAlbum", m_albumBuffer, sizeof(m_albumBuffer));
        
        ImGui::PopStyleColor(2);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        
        // Buttons - right aligned
        bool canSave = m_editingTrack != nullptr && m_titleBuffer[0] != '\0';
        float buttonAreaWidth = 210.0f;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - buttonAreaWidth);
        
        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
        
        if (!canSave)
            ImGui::BeginDisabled();
        
        if (ImGui::Button("Save", ImVec2(100, 0)) || (ImGui::IsKeyPressed(ImGuiKey_Enter) && canSave))
        {
            if (m_onSave && m_editingTrack)
                m_onSave(m_editingTrack, m_titleBuffer, m_artistBuffer, m_albumBuffer);
            Close();
            ImGui::CloseCurrentPopup();
        }
        
        if (!canSave)
            ImGui::EndDisabled();
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel", ImVec2(100, 0)) || ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            Close();
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
        
        ImGui::EndPopup();
    }
    else
    {
        Close();
    }
}

} // namespace moosic