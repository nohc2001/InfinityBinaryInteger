#include "infArray_fm_v0.h"

class infint
{
  public:
	freemem::FM_System0 * fm;
	infArray < byte8 > data;
	bool isPositive = true;
	bool temp = false;

	  infint()
	{
	}

	infint(int num, freemem::FM_System0 * fms)
	{
		init(fms);

		unsigned int nnum = (unsigned int)num;

		if (num >= 0)
			isPositive = true;
		else
		{
			isPositive = false;
			nnum = -num;
		}


		int len = 4;
		if (len > data.array_siz)
		{
			int n = len - data.array_siz;
			for (int i = 0; i < n; ++i)
			{
				data.push((unsigned char)0);
			}
		}

		for (int i = 0; i < len; ++i)
		{
			unsigned int cc = nnum >> (i * 8);
			unsigned char c = (unsigned char)(cc);
			data[i] = c;
		}
	}

	infint(const char *numstr)
	{
	}

	infint(infint & ref)
	{
		init(ref.fm);
		isPositive = ref.isPositive;
		int len = ref.data.array_siz;
		if (len > data.array_siz)
		{
			int n = len - data.array_siz;
			for (int i = 0; i < n; ++i)
			{
				data.push((unsigned char)0);
			}
		}

		for (int i = 0; i < len; ++i)
		{
			data[i] = ref.data[i];
			// discard qualifiers
		}
	}

	virtual ~ infint()
	{
	}

	static infint & t(int num, freemem::FM_System0 * fms)
	{
		infint *result = (infint *) fms->_New(sizeof(infint), true);
		result->init(fms);
		result->operator=(num);
		result->temp = true;
		return *result;
	}

	void init(freemem::FM_System0 * fms)
	{
		fm = fms;
		data.Init(8, fm);
		data.push((unsigned char)0);
		isPositive = true;
	}

	void release()
	{
		data.Release();
	}

	void tempRelease()
	{
		if (temp)
		{
			release();
			fm->_Delete((byte8 *) this, sizeof(infint));
		}
	}

	void printstate()
	{
		if (isPositive)
		{
			cout << "+";
		}
		else
		{
			cout << "-";
		}
		for (int i = 0; i < data.array_siz; ++i)
		{
			cout << "[" << (int)data[i] << "]";
		}
		cout << endl;
	}

	void operator=(infint & num)
	{
		isPositive = num.isPositive;
		int len = num.data.array_siz;
		if (len > data.array_siz)
		{
			int n = len - data.array_siz;
			for (int i = 0; i < n; ++i)
			{
				data.push((unsigned char)0);
			}
		}

		for (int i = 0; i < len; ++i)
		{
			data[i] = num.data[i];
		}

		num.tempRelease();
	}

	void operator=(int num)
	{
		if (num >= 0)
			isPositive = true;
		else
			isPositive = false;

		unsigned int nnum = (unsigned int)num;
		int len = 4;
		if (len > data.array_siz)
		{
			int n = len - data.array_siz;
			for (int i = 0; i < n; ++i)
			{
				data.push((unsigned char)0);
			}
		}

		for (int i = 0; i < len; ++i)
		{
			unsigned int cc = nnum >> (i * 8);
			unsigned char c = (unsigned char)(cc);
			data[i] = c;
		}
	}

	bool operator==(infint & operand)
	{
		if (data.array_siz != operand.data.array_siz)
		{
			operand.tempRelease();
			return false;
		}

		for (int i = 0; i < data.array_siz; ++i)
		{
			if (data[i] != operand.data[i])
			{
				operand.tempRelease();
				return false;
			}
		}

		operand.tempRelease();
		return true;
	}

	bool operator!=(infint & operand)
	{
		if (*this == operand)
		{
			operand.tempRelease();
			return true;
		}
		else
		{
			operand.tempRelease();
			return false;
		}
	}

	bool operator<(infint & operand)
	{
		if (isPositive == false)
		{
			if (operand.isPositive)
			{
				operand.tempRelease();
				return true;
			}

			// all negative
			if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}
			else if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return false;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return true;
				}
			}

			operand.tempRelease();
			// real same
			return false;
		}
		else
		{
			if (operand.isPositive == false)
			{
				operand.tempRelease();
				return false;
			}

			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return true;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return false;
				}
			}

			operand.tempRelease();
			// real same
			return false;
		}
	}

	bool operator<=(infint & operand)
	{
		if (isPositive == false)
		{
			if (operand.isPositive)
			{
				operand.tempRelease();
				return true;
			}

			// all negative
			if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}
			else if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return false;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return true;
				}
			}

			operand.tempRelease();
			// real same
			return true;
		}
		else
		{
			if (operand.isPositive == false)
			{
				operand.tempRelease();
				return false;
			}

			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return true;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return false;
				}
			}

			operand.tempRelease();
			// real same
			return true;
		}
	}

	bool operator>(infint & operand)
	{
		if (isPositive == false)
		{
			if (operand.isPositive)
			{
				operand.tempRelease();
				return false;
			}

			// all negative
			if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}
			else if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return true;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return false;
				}
			}

			operand.tempRelease();
			// real same
			return false;
		}
		else
		{
			if (operand.isPositive == false)
			{
				operand.tempRelease();
				return true;
			}

			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return false;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return true;
				}
			}

			operand.tempRelease();

			// real same
			return false;
		}
	}

	bool operator>=(infint & operand)
	{
		if (isPositive == false)
		{
			if (operand.isPositive)
			{
				operand.tempRelease();
				return false;
			}

			// all negative
			if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}
			else if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return true;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return false;
				}
			}

			operand.tempRelease();
			// real same
			return true;
		}
		else
		{
			if (operand.isPositive == false)
			{
				operand.tempRelease();
				return true;
			}

			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return false;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return true;
				}
			}

			operand.tempRelease();
			// real same
			return true;
		}
	}

	bool absolute_compare(bool left_is_big, bool include_same, infint & operand)
	{
		if (left_is_big)
		{
			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return false;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return true;
				}
			}
		}
		else
		{
			// all positive
			if (data.array_siz < operand.data.array_siz)
			{
				operand.tempRelease();
				return true;
			}
			else if (data.array_siz > operand.data.array_siz)
			{
				operand.tempRelease();
				return false;
			}

			// same length
			for (int i = data.array_siz - 1; i >= 0; --i)
			{
				if (operand.data[i] > data[i])
				{
					operand.tempRelease();
					return true;
				}
				if (operand.data[i] < data[i])
				{
					operand.tempRelease();
					return false;
				}
			}
		}

		// real same
		if (include_same)
		{
			operand.tempRelease();
			return true;
		}
		else
		{
			operand.tempRelease();
			return false;
		}
	}

	infint & operator+(infint & operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = true;

		int len = 0;
		if (data.array_siz < operand.data.array_siz)
		{
			len = operand.data.array_siz;
			result->operator=(operand);
		}
		else
		{
			len = data.array_siz;
			result->operator=(*this);
		}

		if (isPositive == operand.isPositive)
		{
			result->isPositive = isPositive;
			int overflow = 0;
			int i = 0;
			for (i = 0; i < len; ++i)
			{
				unsigned char dc[2] = { 0, 0 };
				if (data.array_siz > i)
					dc[0] = data[i];
				if (operand.data.array_siz > i)
					dc[1] = operand.data[i];
				unsigned char c = dc[0] + dc[1] + overflow;
				result->data[i] = c;
				if (c != 0 && !(dc[0] == 0 || dc[1] == 0))
				{
					c = -dc[0];
					if (c <= dc[1])
						overflow = 1;
					else
						overflow = 0;
				}
				else
					overflow = 0;
			}
			if (overflow == 1)
			{
				result->data.push((unsigned char)overflow);
			}
		}
		else
		{
			int underflow = 0;
			if (absolute_compare(true, false, operand))
			{
				// this is big absolute
				result->isPositive = isPositive;
				int i = 0;
				for (i = 0; i < len; ++i)
				{
					unsigned char dc[2] = { 0, 0 };
					if (data.array_siz > i)
						dc[0] = data[i];
					if (operand.data.array_siz > i)
						dc[1] = operand.data[i];
					unsigned char c = dc[0] - dc[1] - underflow;
					result->data[i] = c;
					if (dc[0] - underflow < dc[1])
						underflow = 1;
					else
						underflow = 0;
				}
			}
			else
			{
				// operand is big absolute
				result->isPositive = operand.isPositive;
				int i = 0;
				for (i = 0; i < len; ++i)
				{
					unsigned char dc[2] = { 0, 0 };
					if (data.array_siz > i)
						dc[0] = data[i];
					if (operand.data.array_siz > i)
						dc[1] = operand.data[i];
					unsigned char c = dc[1] - dc[0] - underflow;
					result->data[i] = c;
					if (dc[1] - underflow < dc[0])
						underflow = 1;
					else
						underflow = 0;
				}
			}
		}
		operand.tempRelease();
		return *result;
	}

	infint & operator-(infint & operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = true;

		int len = 0;
		if (data.array_siz < operand.data.array_siz)
		{
			len = operand.data.array_siz;
			result->operator=(operand);
		}
		else
		{
			len = data.array_siz;
			result->operator=(*this);
		}

		if (isPositive == operand.isPositive)
		{
			int underflow = 0;
			if (absolute_compare(true, false, operand))
			{
				// this is big absolute
				result->isPositive = isPositive;
				int i = 0;
				for (i = 0; i < len; ++i)
				{
					unsigned char dc[2] = { 0, 0 };
					if (data.array_siz > i)
						dc[0] = data[i];
					if (operand.data.array_siz > i)
						dc[1] = operand.data[i];
					unsigned char c = dc[0] - dc[1] - underflow;
					result->data[i] = c;
					if (dc[0] - underflow < dc[1])
						underflow = 1;
					else
						underflow = 0;
				}
			}
			else
			{
				// operand is big absolute
				result->isPositive = !operand.isPositive;
				int i = 0;
				for (i = 0; i < len; ++i)
				{
					unsigned char dc[2] = { 0, 0 };
					if (data.array_siz > i)
						dc[0] = data[i];
					if (operand.data.array_siz > i)
						dc[1] = operand.data[i];
					unsigned char c = dc[1] - dc[0] - underflow;
					result->data[i] = c;
					if (dc[1] - underflow < dc[0])
						underflow = 1;
					else
						underflow = 0;
				}
			}
		}
		else
		{
			result->isPositive = isPositive;
			int overflow = 0;
			int i = 0;
			for (i = 0; i < len; ++i)
			{
				unsigned char dc[2] = { 0, 0 };
				if (data.array_siz > i)
					dc[0] = data[i];
				if (operand.data.array_siz > i)
					dc[1] = operand.data[i];
				unsigned char c = dc[0] + dc[1] + overflow;
				result->data[i] = c;
				if (c != 0)
				{
					c = -dc[0];
					if (c <= dc[1])
						overflow = 1;
					else
						overflow = 0;
				}
				else
					overflow = 0;
			}
			if (overflow == 1)
			{
				result->data.push((unsigned char)overflow);
			}
		}
		operand.tempRelease();
		return *result;
	}

	infint & operator*(infint & operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = false;
		// temp set
		result->isPositive = true;

		for (int a = 0; a < data.array_siz; ++a)
		{
			for (int b = 0; b < operand.data.array_siz; ++b)
			{
				unsigned int addnum = data[a] * operand.data[b];
				if (addnum == 0)
					continue;
				int apb = a + b;
				infint *xnn = (infint *) fm->_New(sizeof(infint), false);
				xnn->init(fm);
				xnn->temp = false;
				// temp set
				xnn->isPositive = true;
				xnn->data.array_siz = 0;

				for (int i = 0; i < apb; ++i)
				{
					xnn->data.push(0);
				}
				unsigned char cc = addnum;
				xnn->data.push(cc);
				cc = addnum >> 8;
				xnn->data.push(cc);

				result->operator=(result->operator+(*xnn));

				xnn->temp = true;
				xnn->tempRelease();
			}
		}

		result->temp = true;
		if (isPositive == operand.isPositive)
		{
			result->isPositive = true;
		}
		else
		{
			result->isPositive = false;
		}

		operand.tempRelease();
		return *result;
	}

	infint & operator/(infint & operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = false;

		infint *dat = (infint *) fm->_New(sizeof(infint), false);
		dat->init(fm);
		dat->operator=(*this);
		dat->temp = false;

		if (*this < operand)
		{
			result->temp = true;
			return *result;
		}

		int oplen = operand.data.array_siz;
		for (int op = operand.data.array_siz; op >= 0; --op)
		{
			if (operand.data[op] == 0)
			{
				--oplen;
			}
			else
			{
				break;
			}
		}

		int datlen = operand.data.array_siz;
		for (int op = operand.data.array_siz; op >= 0; --op)
		{
			if (data[op] == 0)
			{
				--datlen;
			}
			else
			{
				break;
			}
		}

		int seek = datlen - oplen + 1;
		for (int i = seek - 1; i >= 0; --i)
		{
			infint *num = (infint *) fm->_New(sizeof(infint), false);
			num->init(fm);
			for(int k=0;k<i;++k){
				num->data.push(0);
			}
			num->temp = false;

			int n = seek - 1 - i;
			unsigned int pp = 0;
			if(datlen-n+1 > datlen){
				pp = data[datlen - n] ;
			}
			else{
				pp = data[datlen - n+1] * 256 + data[datlen - n];
			}
			int rmin = pp / operand.data[oplen - n];
			int rmax = pp / ((unsigned int)operand.data[oplen - n] + 1);
			for (int k = rmin; k <= rmax; ++k)
			{
				infint *datcopy = (infint *) fm->_New(sizeof(infint), false);
				datcopy->init(fm);
				datcopy->operator=(*dat);
				datcopy->temp = false;
				
				num->data[i-1] = k;
				
				datcopy->operator=(datcopy->operator-((operand * (*num))));
				if (*datcopy >= operand)
				{
					continue;
				}
				else{
					dat->operator=(*datcopy);
					datcopy->temp = true;
					datcopy->tempRelease();
					result->operator=(result->operator+(*num));
					break;
				}
			}
			
			num->temp = true;
			num->tempRelease();
		}
		
		dat->temp = true;
		dat->tempRelease();

		operand.tempRelease();
		
		result->temp = true;
		return *result;
	}

	infint& operator%(infint& operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = false;
		
		infint *tt = (infint *) fm->_New(sizeof(infint), false);
		tt->init(fm);
		tt->operator=(0);
		tt->temp = false;
		*tt = *this / operand;
		*result = *this - *tt;
		tt->temp = true;
		tt->tempRelease();
		
		operand.tempRelease();
		
		result->temp = true;
		return *result;
	}

	infint& operator^(infint& operand)
	{
		infint *result = (infint *) fm->_New(sizeof(infint), false);
		result->init(fm);
		result->operator=(0);
		result->temp = false;
		
		return *result;
	}
};

int main()
{
	freemem::FM_System0 sys;
	sys.SetHeapData(4096, 4096, 4096, 4096);
	infint num(7123, &sys);
	infint num2(2525, &sys);
	// num.init(&sys);
	// num = 2000;
	num.printstate();
	num2.printstate();
	num = num / num2;
	num.printstate();
	num.release();
	return 0;
}