#ifndef TOOL_H
#define TOOL_H

#include<vector>

using namespace std;

//���vector�����ͷ��ڴ�
template<typename T>
void freeVector(vector<T*>&v) {
	vector<T*>::iterator iter = v.begin();
	while (iter != v.end()) {
		cout << "***************  Free " << (*iter)->getName() << endl;
		delete *iter;
		iter = v.erase(iter);
	}
	vector<T*>(v).swap(v);//����swap�������������ͷ�vector���ڴ�ռ䣬clearֻ���Ԫ�أ����ͷ��ڴ�
}

//�ж�ĳʵ���Ƿ���ĳvector��
template<typename T>
bool isInVector(vector<T*>&v, T* target) {
	for (auto iter = v.begin(); iter != v.end();) {
		if (*iter == target) {
			return true;
		}
		else {
			++iter;
		}
	}
	return false;
}

//���vector��ָ��Ԫ��
template<typename T> void removeVectorMember(vector<T*>&v, T* target, bool clearRepeatedMember = true) {
	for (auto iter = v.begin(); iter != v.end();) {
		if (*iter == target) {
			iter = v.erase(iter);
			if (!clearRepeatedMember)
				return;
		}
		else {
			++iter;
		}
	}
}

//���vector��ָ��Ԫ�أ����ͷŸ�Ԫ���ڴ�
template<typename T> void removeAndFreeVectorMember(vector<T*>&v, T* target, bool clearRepeatedMember = true) {
	for (auto iter = v.begin(); iter != v.end();) {
		if (*iter == target) {
			cout << "***************  Free " << (*iter)->getName() << endl;
			delete *iter;
			iter = v.erase(iter);
			if (!clearRepeatedMember)
				return;
		}
		else {
			++iter;
		}
	}
}

#endif