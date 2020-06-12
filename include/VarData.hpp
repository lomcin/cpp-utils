#ifndef _H_VAR_DATA_H_
#define _H_VAR_DATA_H_

class VarData {
	int *data;
	
	public:
	VarData() {
		data = NULL;
	}

	template<typename DataType>	
	VarData(DataType v) {
		data = (int*)new DataType(v);
	}

	~VarData() {
		if(data) delete data;
		data = NULL;
	}
	
	template<typename DataType>	
	DataType &operator=(const DataType v) {
		if (data) delete data;
		data = (int*)new DataType(v);
		return (DataType&)(*((DataType*)data));
	}
	
	template<typename DataType>	
	operator DataType&() {
		return (DataType&)(*((DataType*)this->data));
	}
};

#endif //_H_VAR_DATA_H_