#ifndef TOOL_H
#define TOOL_H

#include<vector>

using namespace std;

//清空vector，并释放内存
template<typename T>
void freeVector(vector<T*>&v) {
	vector<T*>::iterator iter = v.begin();
	while (iter != v.end()) {
		cout << "***************  Free " << (*iter)->getName() << endl;
		delete *iter;
		iter = v.erase(iter);
	}
	vector<T*>(v).swap(v);//调用swap函数可以真正释放vector的内存空间，clear只清除元素，不释放内存
}

//判断某实例是否在某vector中
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

//清除vector中指定元素
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

//清除vector中指定元素，并释放该元素内存
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