#pragma once
#include "Misc.h"
#include "SystemBase.h"

#include "Graphics.h"
#include "SCEnvelope.h"
#include "SCTree.h"
class SCTreeSystem : public SystemBase {
public:
	void OnCreate();

	void BuildEnvelope();

	void BuildTree();

	void RemoveTree();

	void RemoveEnvelope();

	void OnDestroy();

	void Update();
	
	void FixedUpdate();
private:
	Material* _EnvelopePointMaterial;
	Texture* _EnvelopeTexture;
	Material* _TreePointMaterial;
	Texture* _TreePointTexture;
	Material* _TreeMeshMaterial;
	Texture* _TreeMeshTexture;
	Material* _TreeLeafMaterial;
	Texture* _TreeLeafTexture;

	float _EnvelopeRadius, _MaxHeight, _MinHeight;
	int _PointsCount;

	SCEnvelope* _Envelope;
	int _SelectedEnvelopeType;
	float _GrowDist, _AttractDitsMult, _RemoveDistMult, _AttractDist, _RemoveDist;
	int _Iteration;
	SCTree* _Tree;

	inline void EnvelopeGUIMenu();
	inline void TreeGUIMenu();
};
