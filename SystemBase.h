#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

class SystemBase {
public:
	SystemBase() { _Enabled = false; }
	virtual void OnCreate() {}
	virtual void OnDestroy() {}
	virtual void OnStartRunning() {}
	virtual void OnStopRuning() {}
	virtual void Update() = 0;
	SystemType GetSystemType() { return _SystemType; }
	void Enable() {
		if (!_Enabled) {
			_Enabled = true;
			OnStartRunning();
		}
	}
	void Disable() {
		if (_Enabled) {
			_Enabled = false;
			OnStopRuning();
		}
	}

	bool IsEnabled() {
		return _Enabled;
	}

public:
	bool _Enabled;
	SystemType _SystemType = SystemType::DefaultSystemType;
};
#endif SYSTEMBASE_H
