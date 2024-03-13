/*
MIT License

Copyright (c) 2020-2024 Lucas Maggi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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