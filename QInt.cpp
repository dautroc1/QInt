#include<iostream>
#include<cmath>
#include<bitset>
#include <string>
#include <typeinfo>
#include<vector>
#include<fstream>
using namespace std;
string Binary[128];
string HexToBi[16]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
string multiply(string num1, string num2) 
{ 
    int len1 = num1.size(); 
    int len2 = num2.size(); 
    if (len1 == 0 || len2 == 0) 
    return "0"; 
  
    // will keep the result number in vector 
    // in reverse order 
    vector<int> result(len1 + len2, 0); 
  
    // Below two indexes are used to find positions 
    // in result.  
    int i_n1 = 0;  
    int i_n2 = 0;  
      
    // Go from right to left in num1 
    for (int i=len1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int n1 = num1[i] - '0'; 
  
        // To shift position to left after every 
        // multiplication of a digit in num2 
        i_n2 = 0;  
          
        // Go from right to left in num2              
        for (int j=len2-1; j>=0; j--) 
        { 
            // Take current digit of second number 
            int n2 = num2[j] - '0'; 
  
            // Multiply with current digit of first number 
            // and add result to previously stored result 
            // at current position.  
            int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
  
            // Carry for next iteration 
            carry = sum/10; 
  
            // Store result 
            result[i_n1 + i_n2] = sum % 10; 
  
            i_n2++; 
        } 
  
        // store carry in next cell 
        if (carry > 0) 
            result[i_n1 + i_n2] += carry; 
  
        // To shift position to left after every 
        // multiplication of a digit in num1. 
        i_n1++; 
    } 
  
    // ignore '0's from the right 
    int i = result.size() - 1; 
    while (i>=0 && result[i] == 0) 
    i--; 
  
    // If all were '0's - means either both or 
    // one of num1 or num2 were '0' 
    if (i == -1) 
    return "0"; 
  
    // generate the result string 
    string s = ""; 
      
    while (i >= 0) 
        s += std::to_string(result[i--]); 
  
    return s; 
}
string findSum(string str1, string str2) 
{ 
    // Before proceeding further, make sure length 
    // of str2 is larger. 
    if (str1.length() > str2.length()) 
        swap(str1, str2); 
  
    // Take an empty string for storing result 
    string str = ""; 
  
    // Calculate length of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    // Reverse both of strings 
    reverse(str1.begin(), str1.end()); 
    reverse(str2.begin(), str2.end()); 
  
    int carry = 0; 
    for (int i=0; i<n1; i++) 
    { 
        // Do school mathematics, compute sum of 
        // current digits and carry 
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
  
        // Calculate carry for next step 
        carry = sum/10; 
    } 
  
    // Add remaining digits of larger number 
    for (int i=n1; i<n2; i++) 
    { 
        int sum = ((str2[i]-'0')+carry); 
        str.push_back(sum%10 + '0'); 
        carry = sum/10; 
    } 
  
    // Add remaining carry 
    if (carry) 
        str.push_back(carry+'0'); 
  
    // reverse resultant string 
    reverse(str.begin(), str.end()); 
  
    return str; 
} 
bool isSmaller(string str1, string str2) 
{ 
    // Calculate lengths of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    if (n1 < n2) 
    return true; 
    if (n2 < n1) 
    return false; 
  
    for (int i=0; i<n1; i++) 
    if (str1[i] < str2[i]) 
        return true; 
    else if (str1[i] > str2[i]) 
        return false; 
  
    return false; 
} 
string findDiff(string str1, string str2) 
{ 
    // Before proceeding further, make sure str1 
    // is not smaller 
    if (isSmaller(str1, str2)) 
        swap(str1, str2); 
  
    // Take an empty string for storing result 
    string str = ""; 
  
    // Calculate length of both string 
    int n1 = str1.length(), n2 = str2.length(); 
  
    // Reverse both of strings 
    reverse(str1.begin(), str1.end()); 
    reverse(str2.begin(), str2.end()); 
      
    int carry = 0; 
  
    // Run loop till small string length 
    // and subtract digit of str1 to str2 
    for (int i=0; i<n2; i++) 
    { 
        // Do school mathematics, compute difference of 
        // current digits 
          
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry); 
          
        // If subtraction is less then zero 
        // we add then we add 10 into sub and 
        // take carry as 1 for calculating next step 
        if (sub < 0) 
        { 
            sub = sub + 10; 
            carry = 1; 
        } 
        else
            carry = 0; 
  
        str.push_back(sub + '0'); 
    } 
  
    // subtract remaining digits of larger number 
    for (int i=n2; i<n1; i++) 
    { 
        int sub = ((str1[i]-'0') - carry); 
          
        // if the sub value is -ve, then make it positive 
        if (sub < 0) 
        { 
            sub = sub + 10; 
            carry = 1; 
        } 
        else
            carry = 0; 
              
        str.push_back(sub + '0'); 
    } 
  
    // reverse resultant string 
    reverse(str.begin(), str.end()); 
  
    return str; 
}
void Set()
{
	for(int i=0;i<63;i++)
	{
		Binary[i]=to_string(_int64(pow(2,i)));
	}
	for(int i=63;i<128;i++)
	{
		Binary[i]=multiply(Binary[i-1],"2");
	}
}

class QInt
{
public:
	_int64 arrayBits[2];
public:
	QInt()
	{
		arrayBits[0]=0;
		arrayBits[1]=0;
		Set();
	}
	void Out()
	{
		cout<<arrayBits[1];
	}
	void Plus1(bitset<64> &temp,bitset<64> &temp1)
	{
		int x=1,i=0;
		while((i<=127)&&(x==1))
		{
			if(i>63)
			{
				int j=i-63;
				if(temp[j]==0)
				{
					temp[j]=1;
					x=0;
					return;
				}
				if(temp[j]==1)
				{
					temp[j]=0;
					x=1;
				}
			}
			else
			{
				if(temp1[i]==0)
				{
					temp1[i]=1;
					x=0;
					return;
				}
				if(temp1[i]==1)
				{
					temp1[i]=0;
					x=1;
				}
			}
			i++;
		}
		
	}
	void Setbit(bitset<64> *temp,bitset<64> *temp1,int i,int bit)
	{
		
		
		if(i>63)
		{
			i=i-64;
			i=63-i;
			temp1->set(i,bit);
			
			
		}
		else
		{
			i=63-i;
			temp->set(i,bit);
			
		}
	}
	string longDivision(string number) 
{ 
    string ans;
	int index=0;
	int temp1=number[index]-'0';
	int temp3,i=0;
	
	 while (temp1 < 2) 
	 {
		 if(number.length()==1)
		 {
			 return "0";

		 }
       temp1 = temp1 * 10 + (number[++index] - '0'); 
	 }
	while(number.size()>index)
	{
	//temp3=temp1/2;
	//ans='0'+temp3;
		ans += (temp1 / 2) + '0';
	temp1=(temp1 % 2) * 10 + number[++index] - '0'; 
	}

    if (ans.length() == 0) 
        return "0"; 
      
    
    return ans; 
} 
	void DeleteFirst0(string &number)
	{
		int len=number.length(),i=0;
		while(true)
		{
			if(number[i]=='0')
			{
				number.erase(0,1);
				
			}
			else
			{
				return;
			}

		}
	}
	string Tostring()
	{
		string temp;
		int x;
		for(int i=63;i>=0;i--)
		{
			x=(arrayBits[0] >> i) & 1;
			temp.append(to_string(x));
		}
		for(int i=63;i>=0;i--)
		{
			x=(arrayBits[1] >> i) & 1;
			temp.append(to_string(x));
		}
		return temp;
	}
	string InputBinary(string Bi)
	{
		int len;
		int bit;
		
		len=Bi.length();
		bitset<64> temp;
		bitset<64> temp1;
		temp.reset();
		temp1.reset();
		int i=0;
		int j=127;
		while(Bi!="")
		{
			if((i>=127)||(i>len-1))
				 break;
			len=Bi.length();
			bit=(Bi[len-1-i]-48)%2;
			Setbit(&temp,&temp1,j,bit);
			
			i++;
			j--;
			

		}
		arrayBits[0]=temp.to_ullong();
		arrayBits[1]=temp1.to_ullong();
		return Bi;
	}
	string ConvertDeToBi(string De)
	{
		int i=127,choice=0;
		bitset<64> temp;
		bitset<64> temp1;
		temp.reset();
		temp1.reset();
		string value;
		int len=De.length();
		int bit;
		int j=0;
		char a='-';
		if(De.at(0)==a)
		{
			choice=1;
			
			De=De.substr(1);
		}
		while(De!="")
		{
			len=De.length();
			bit=(De[len-1]-48)%2;
			if(choice!=1)
				value.insert(0,to_string(bit));
			Setbit(&temp,&temp1,i,bit);
			De=longDivision(De);
			if(De=="0")
				break;
			if(i<0)
				break;
			i--;
		}
		if(choice==1)
		{
			temp.flip();
			temp1.flip();
			Plus1(temp,temp1);
			value.insert(0,temp1.to_string());
			value.insert(0,temp.to_string());
		}
		arrayBits[0]=temp.to_ullong();
		arrayBits[1]=temp1.to_ullong();
		
		return value;
	}
	string ConvertBiToDe(string Bi)
	{
		int len;
		int bit;
		
		len=Bi.length();
		bitset<64> temp;
		bitset<64> temp1;
		temp.reset();
		temp1.reset();
		int i=0;
		int j=127;
		string value="0";
		if((len==128)&&(Bi[0]=='1'))
		{
			
			while(Bi!="")
			{
				if(i>126)
					 break;
				len=Bi.length();
				bit=(Bi[len-1-i]-48)%2;
				
				Setbit(&temp,&temp1,j,bit);
				if(bit==1)
					value=findSum(value,Binary[i]);
				i++;
				j--;

			}
			value=findDiff(value,Binary[127]);
			DeleteFirst0(value);
			value.insert(0,"-");
		arrayBits[0]=temp.to_ullong();
		arrayBits[1]=temp1.to_ullong();
		return value;
		}
		
		while(Bi!="")
		{
			if((i>=127)||(i>len-1))
				 break;
			len=Bi.length();
			bit=(Bi[len-1-i]-48)%2;
			Setbit(&temp,&temp1,j,bit);
			if(bit==1)
				value=findSum(value,Binary[i]);
			i++;
			j--;
			

		}
		arrayBits[0]=temp.to_ullong();
		arrayBits[1]=temp1.to_ullong();
		return value;
	}
	string ConvertHexToBi(string Hex)
	{
		int choice=0;
		if(Hex.length()==32)
		{
			if((Hex[0]=='A')||(Hex[0]=='B')||(Hex[0]=='C')||(Hex[0]=='D')||(Hex[0]=='E')||(Hex[0]=='F'))
			{
				choice=1;
			}
		}
		string value;
		int index=0;
		for(int i=0;i<Hex.length();i++)
		{
			if(Hex[i]=='A')
				index=10;
			if(Hex[i]=='B')
				index=11;
			if(Hex[i]=='C')
				index=12;
			if(Hex[i]=='D')
				index=13;
			if(Hex[i]=='E')
				index=14;
			if(Hex[i]=='F')
				index=15;
			if((Hex[i]-48>=0)&&(Hex[i]-48<=9))
				index=Hex[i]-48;
			value.append(HexToBi[index]);
		}
		/*if(choice==1)
		{
			int len;
		int bit;
		
		len=value.length();
		bitset<64> temp;
		bitset<64> temp1;
		temp.reset();
		temp1.reset();
		int i=0;
		int j=127;
			while(value!="")
			{
				if((i>127)||(i>len-1))
					 break;
				len=value.length();
				bit=(value[len-1-i]-48)%2;
				Setbit(&temp,&temp1,j,bit);
			
				i++;
				j--;
			

			}
			temp.flip();
			temp1.flip();
			Plus1(temp,temp1);
			value.clear();
			value.insert(0,temp1.to_string());
			value.insert(0,temp.to_string());
		}*/
		InputBinary(value);
		return value;
	}
	string ConvertBiToHex(string Bi)
	{
		string temp;
		int len=Bi.length();
		int len1;
		if(len%4!=0)
		{
			for(int i=0;i<4-len%4;i++)
			{
				Bi.insert(0,"0");
			}
			len1=len/4+1;
		}
		else
			len1=len/4;
		len=Bi.length();
		for(int i=0;i<len1;i++)
		{
			for(int j=0;j<16;j++)
			{
				if(Bi.substr(len-4*(i+1),4)==HexToBi[j])
				{
					if((i==len1-1)&&(j==0))
						break;
					if(j==10)
						temp.insert(0,"A");
					if(j==11)
						temp.insert(0,"B");
					if(j==12)
						temp.insert(0,"C");
					if(j==13)
						temp.insert(0,"D");
					if(j==14)
						temp.insert(0,"E");
					if(j==15)
						temp.insert(0,"F");
					if((j>=0)&&(j<=9))
						temp.insert(0,to_string(int(j)));
					break;
				}
			}
		}
		
		
		return temp;
	}
	string ConvertDeToHex(string De)
	{
		string temp=ConvertDeToBi(De);
		DeleteFirst0(temp);
		InputBinary(temp);
		return ConvertBiToHex(temp);
	}
	string ConvertHexToDe(string Hex)
	{
		string temp=ConvertHexToBi(Hex);
		DeleteFirst0(temp);
		InputBinary(temp);
		return ConvertBiToDe(temp);
	}
	 QInt& operator =(const QInt &);
	 QInt operator +(const QInt&);
	 QInt operator -(const QInt&);
	 QInt operator  *(const QInt&);
	 QInt operator  /(const QInt&);
	 QInt operator ~();
	 QInt operator &(QInt b);
	 QInt operator |(QInt b);
	 QInt operator ^(QInt b);
	 QInt operator <<(int b);
	 QInt operator >>(int b);
	 QInt ror();
	 QInt rol();
};
void Run(string path,string path1)
{
	int i=0,choice=0,shift;
	string temp,temp1,temp2;
	string value;
	QInt a,b,result;
	ifstream fin;
	fin.open(path);
	ofstream fout;
	fout.open(path1);
	while(!fin.eof())
	{
		choice=0;
		fin>>temp;
		fin>>temp1;
		if((atoi(temp.c_str())==2)&&(atoi(temp1.c_str())==10))
		{
			choice=1;
			
			fin>>value;
			fout<<a.ConvertBiToDe(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==10)&&(atoi(temp1.c_str())==2))
		{
			choice=1;
			
			fin>>value;
			fout<<a.ConvertDeToBi(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==2)&&(atoi(temp1.c_str())==16))
		{
			choice=1;
			
			fin>>value;
			fout<<a.ConvertBiToHex(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==16)&&(atoi(temp1.c_str())==2))
		{
			choice=1;
		
			fin>>value;
			fout<<a.ConvertHexToBi(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==10)&&(atoi(temp1.c_str())==16))
		{
			choice=1;
			
			fin>>value;
			fout<<a.ConvertDeToHex(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==16)&&(atoi(temp1.c_str())==10))
		{
			choice=1;
			
			fin>>value;
			fout<<a.ConvertHexToDe(value)<<endl;
			continue;
		}
		if((atoi(temp.c_str())==2)&&(atoi(temp1.c_str())==2))
		{
			choice=1;
			fin>>value;
			a.InputBinary(value);
			a.DeleteFirst0(value);
			fout<<value<<endl;
			continue;
		}
		if((atoi(temp.c_str())==10)&&(atoi(temp1.c_str())==10))
		{
			choice=1;
			fin>>value;
			a.ConvertDeToBi(value);
			a.DeleteFirst0(value);
			fout<<value<<endl;
			continue;
		}
		if((atoi(temp.c_str())==16)&&(atoi(temp1.c_str())==16))
		{
			choice=1;
			fin>>value;
			a.ConvertHexToBi(value);
			a.DeleteFirst0(value);
			fout<<value<<endl;
			continue;
		}
		/*if(atoi(temp.c_str())==2||atoi(temp.c_str())==10||atoi(temp.c_str())==16)
		{

			if(temp1=="~")
			{
				choice=1;
				fin>>temp1;
				if(atoi(temp.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp.c_str())==16)
					a.ConvertHexToBi(temp1);
				a=~a;
				value=a.Tostring();
				a.DeleteFirst0(value);
				fout<<value<<endl;
				continue;
			}
			if(temp1=="rol")
			{
				choice=1;
				fin>>temp1;
				if(atoi(temp.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp.c_str())==16)
					a.ConvertHexToBi(temp1);
				a=a.rol();
				value=a.Tostring();
				a.DeleteFirst0(value);
				fout<<value<<endl;
				continue;
			}
			if(temp1=="ror")
			{
				choice=1;
				fin>>temp1;
				if(atoi(temp.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp.c_str())==16)
					a.ConvertHexToBi(temp1);
				a=a.ror();
				value=a.Tostring();
				a.DeleteFirst0(value);
				fout<<value<<endl;
				continue;
			}
			fin>>temp2;
			if(temp2=="+")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a+b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="-")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a-b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="*")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a*b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="/")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a/b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="^")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a^b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="<<")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				shift=atoi(temp1.c_str());
				result=a<<shift;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2==">>")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				shift=atoi(temp1.c_str());
				result=a>>shift;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="|")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a|b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
			if(temp2=="&")
			{
				choice=1;
				if(atoi(temp1.c_str())==2)
					a.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					a.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					a.ConvertHexToBi(temp1);
				fin>>temp1;
				if(atoi(temp1.c_str())==2)
					b.InputBinary(temp1);
				if(atoi(temp1.c_str())==10)
					b.ConvertDeToBi(temp1);
				if(atoi(temp1.c_str())==16)
					b.ConvertHexToBi(temp1);
				result=a&b;
				value=result.Tostring();
				result.DeleteFirst0(value);
				fout<<value<<endl;
				continue;

			}
		}*/
		if(choice==0)
		{
			getline(fin,value,'\n');
			fout<<endl;
		}
		i++;
	}
}
 
int main()
{
	
		
}
