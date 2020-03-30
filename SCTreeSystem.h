#pragma once
#include "Misc.h"
#include "SystemBase.h"

#include "Material.h"
#include "Texture.h"
#include "SCEnvelope.h"
#include "SCTree.h"
class SCTreeSystem : public SystemBase {
public:
	SCTreeSystem() : SystemBase() {
	}
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
	Material* _TreeBranchMaterial;
	Texture* _BranchTexture;

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
