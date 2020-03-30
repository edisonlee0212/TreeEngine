#include "SCTreeSystem.h"



#include "SurfaceOfRevolutionEnvelope.h"
#include "CylinderEnvelope.h"
#include "CubeEnvelope.h"


void SCTreeSystem::OnCreate() {
	_EnvelopePointMaterial = new Material();
	_EnvelopePointMaterial->shader = new Shader(FileSystem::GetPath("Shaders/Vertex/LightDefaultInstanced.vert"), FileSystem::GetPath("Shaders/Fragment/LightDefault.frag"));
	_EnvelopeTexture = new Texture();
	_EnvelopeTexture->LoadTexture(FileSystem::GetPath("src/Materials/Textures/white.png"), "");
	_EnvelopePointMaterial->textures.push_back(_EnvelopeTexture);

	_TreeBranchMaterial = new Material();
	_TreeBranchMaterial->shader = new Shader(FileSystem::GetPath("Shaders/Vertex/LightDefaultInstanced.vert"), FileSystem::GetPath("Shaders/Fragment/LightDefault.frag"));
	_BranchTexture = new Texture();
	_BranchTexture->LoadTexture(FileSystem::GetPath("Textures/brown.png"), "");
	_TreeBranchMaterial->textures.push_back(_BranchTexture);
	_GrowDist = 0.3f;
	_AttractDitsMult = 3.0f;
	_RemoveDistMult = 0.5f;
	_EnvelopeRadius = 4.0f;
	_MaxHeight = 4.0f;
	_MinHeight = 1.0f;
	_PointsCount = 1600;
	Enable();
}

void SCTreeSystem::BuildEnvelope() {
	RemoveEnvelope();
	switch (_SelectedEnvelopeType)
	{
	case 0:
		_Envelope = new SurfaceOfRevelutionEnvelope(_EnvelopeRadius, _MaxHeight, _EnvelopeRadius, -_EnvelopeRadius, _MinHeight, -_EnvelopeRadius, _EnvelopePointMaterial);
		break;
	case 1:
		_Envelope = new CubeEnvelope(_EnvelopeRadius, _MaxHeight, _EnvelopeRadius, -_EnvelopeRadius, _MinHeight, -_EnvelopeRadius, _EnvelopePointMaterial);
		break;
	case 2:
		_Envelope = new CylinderEnvelope(_EnvelopeRadius, _MaxHeight, _EnvelopeRadius, -_EnvelopeRadius, _MinHeight, -_EnvelopeRadius, _EnvelopePointMaterial);
		break;
	default:
		_Envelope = new SurfaceOfRevelutionEnvelope(_EnvelopeRadius, _MaxHeight, _EnvelopeRadius, -_EnvelopeRadius, _MinHeight, -_EnvelopeRadius, _EnvelopePointMaterial);
		break;
	}
	Debug::Log("Generating attraction points...");
	_Envelope->GeneratePoints(_PointsCount);
	Debug::Log("Attraction points generation complete. [Amount: " + std::to_string(_PointsCount) + "]");
}


void SCTreeSystem::BuildTree() {
	if (_Envelope == nullptr || !_Envelope->PointsGenerated()) BuildEnvelope();
	RemoveTree();
	_Iteration = 0;
	_Tree = new SCTree(glm::vec3(0.0f), _TreeBranchMaterial);
	_AttractDist = _GrowDist * _AttractDitsMult;
	_RemoveDist = _GrowDist * _RemoveDistMult;
	Debug::Log("Trunk growing...");
	_Tree->GrowTrunk(_GrowDist, _AttractDist, _Envelope, glm::vec3(0.0f));
	Debug::Log("Trunk grow complete.");
}

void SCTreeSystem::RemoveTree() {
	if (_Tree != nullptr) delete _Tree;
	_Tree = nullptr;
}

void SCTreeSystem::RemoveEnvelope() {
	if (_Envelope != nullptr) delete _Envelope;
	_Envelope = nullptr;
}

void SCTreeSystem::OnDestroy() {
	Disable();
	delete _EnvelopePointMaterial;
	delete _EnvelopeTexture;
	delete _TreeBranchMaterial;
	delete _BranchTexture;
	RemoveEnvelope();
	RemoveTree();
}

static const char* EnvelopeTypes[]{ "SurfaceOfRevo", "Cube", "Cylinder" };

void SCTreeSystem::Update() {
	EnvelopeGUIMenu();
	TreeGUIMenu();
	if (_Envelope != nullptr) _Envelope->Draw();
	if (_Tree != nullptr) _Tree->Draw();
}

void SCTreeSystem::FixedUpdate() {
	if (_Envelope != nullptr && _Tree != nullptr && _Tree->needsToGrow) {
		_Iteration++;
		_Tree->Grow(_GrowDist, _AttractDist, _RemoveDist, _Envelope, glm::vec3(0.0f), 0.015f, 0.1f, 0.05f, 0.05f);
	}
}

inline void SCTreeSystem::EnvelopeGUIMenu() {
	ImGui::Begin("Envelope Controller");
	ImGui::Combo("Envelope Type", &_SelectedEnvelopeType, EnvelopeTypes, IM_ARRAYSIZE(EnvelopeTypes), 3);
	if (ImGui::Button("Create Aattraction Points")) BuildEnvelope();
	ImGui::SliderInt("Point Amount", &_PointsCount, 100, 3200);
	ImGui::SliderFloat("Envelope Radius", &_EnvelopeRadius, 1.0f, 5.0f);
	ImGui::SliderFloat("Minmum Height", &_MinHeight, 0.1f, _MaxHeight);
	ImGui::SliderFloat("Maximum Height", &_MaxHeight, _MinHeight, 10.0f);
	if (ImGui::Button("Clear Aattraction Points")) RemoveEnvelope();
	ImGui::End();
}

inline void SCTreeSystem::TreeGUIMenu() {
	ImGui::Begin("Tree Controller");
	ImGui::SliderFloat("Grow Distance", &_GrowDist, 0.2f, 0.5f);
	ImGui::SliderFloat("Attract Distance Multiplier", &_AttractDitsMult, 1.0f, 5.0f);
	ImGui::SliderFloat("Remove Distance Multiplier", &_RemoveDistMult, 0.1f, 0.9f);
	if (ImGui::Button("Build Tree")) BuildTree();
	if (ImGui::Button("Delete Tree")) RemoveTree();
	ImGui::Text("Iteration = %d", _Iteration);
	ImGui::End();
}