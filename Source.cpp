#include<iostream>  
#include<stdio.h>
#include<string>  
using namespace std;

struct Node
{
	double weight;
	string ch;
	string code;
	int lchild, rchild, parent;
};

void Select(Node huffTree[], int *a, int *b, int n)//找权值最小的两个a和b  
{
	int i;
	double weight = 0; //找最小的数
	for (i = 0; i <n; i++)
	{
		if (huffTree[i].parent != -1)     //判断节点是否已经选过
			continue;
		else
		{
			if (weight == 0)
			{
				weight = huffTree[i].weight;
				*a = i;
			}
			else
			{
				if (huffTree[i].weight < weight)
				{
					weight = huffTree[i].weight;
					*a = i;
				}
			}
		}
	}
	weight = 0; //找第二小的数
	for (i = 0; i < n; i++)
	{
		if (huffTree[i].parent != -1 || (i == *a))//排除已选过的数
			continue;
		else
		{
			if (weight == 0)
			{
				weight = huffTree[i].weight;
				*b = i;
			}
			else
			{
				if (huffTree[i].weight  < weight)
				{
					weight = huffTree[i].weight;
					*b = i;
				}
			}
		}
	}
	int temp;
	if (huffTree[*a].lchild < huffTree[*b].lchild)  //小的数放左边
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

void Huff_Tree(Node huffTree[], int w[], string ch[], int n)
{
	for (int i = 0; i < 2 * n - 1; i++) //初始过程
	{
		huffTree[i].parent = -1;
		huffTree[i].lchild = -1;
		huffTree[i].rchild = -1;
		huffTree[i].code = "";
	}
	for (int i = 0; i < n; i++)
	{
		huffTree[i].weight = w[i];
		huffTree[i].ch = ch[i];
	}
	for (int k = n; k < 2 * n - 1; k++)
	{
		int i1 = 0;
		int i2 = 0;
		Select(huffTree, &i1, &i2, k); //将i1，i2节点合成节点k
		huffTree[i1].parent = k;
		huffTree[i2].parent = k;
		huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
		huffTree[k].lchild = i1;
		huffTree[k].rchild = i2;
	}
}

void Huff_Code(Node huffTree[], int n)
{
	int i, j, k;
	string s = "";
	for (i = 0; i < n; i++)
	{
		s = "";
		j = i;
		while (huffTree[j].parent != -1) //从叶子往上找到根节点
		{
			k = huffTree[j].parent;
			if (j == huffTree[k].lchild) //如果是根的左子，则记为0
			{
				s = s + "0";
			}
			else
			{
				s = s + "1";
			}
			j = huffTree[j].parent;
		}
		std::cout << "子信息块 " << huffTree[i].ch << " 的编码：";
		for (int l = s.size() - 1; l >= 0; l--)
		{
			std::cout << s[l];
			huffTree[i].code += s[l]; //保存编码
		}
		std::cout << endl;
	}
}

string Huff_Decode(Node huffTree[], int n, string s)
{
	std::cout << "解码后为：" << endl;
	string temp = "", str = "";//保存解码后的字符串
	for (int i = 0; i < s.size(); i++)
	{
		temp = temp + s[i];
		for (int j = 0; j < n; j++)
		{
			if (temp == huffTree[j].code)
			{
				str = str + huffTree[j].ch;
				temp = "";
				break;
			}
			else if (i == s.size() - 1 && j == n - 1 && temp != "")//全部遍历后没有
			{
				str = "解码错误！";
			}
		}
	}
	return str;
}

int main()
{
	FILE* fphzk = NULL;
	int i, j, k, offset;
	int flag, l, temp1;
	int a = 1;
	int cm1 = 0;
	unsigned char buffer[32];
	int character[256];
	for (i = 0; i < 256; i++) { character[i] = 0; };
	int dcharacter[256];
	for (i = 0; i < 256; i++) { dcharacter[i] = 0; };
	char childid[64];
	for (i = 0; i < 64; i++) { childid[i] = 0; };
	int nchildid[64];
	for (i = 0; i < 64; i++) { nchildid[i] = 0; };
	int freq[16];
	for (i = 0; i < 16; i++) { freq[i] = 0; };
	cout << "输入你想要的汉字：	" ;
	unsigned char Character[3];
	cin >> Character;
 	unsigned char key[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
	//预设子信息块值
	int m1[4] = { 0, 0, 0, 0 };
	int m2[4] = { 0, 0, 0, 1 };
	int m3[4] = { 0, 0, 1, 0 };
	int m4[4] = { 0, 0, 1, 1 };
	int m5[4] = { 0, 1, 0, 0 };
	int m6[4] = { 0, 1, 0, 1 };
	int m7[4] = { 0, 1, 1, 0 };
	int m8[4] = { 0, 1, 1, 1 };
	int m9[4] = { 1, 0, 0, 0 };
	int m10[4] = { 1, 0, 0, 1 };
	int m11[4] = { 1, 0, 1, 0 };
	int m12[4] = { 1, 0, 1, 1 };
	int m13[4] = { 1, 1, 0, 0 };
	int m14[4] = { 1, 1, 0, 1 };
	int m15[4] = { 1, 1, 1, 0 };
	int m16[4] = { 1, 1, 1, 1 };
	//输出点阵字符
	{
		fphzk = fopen("HZK16", "rb");
		if (fphzk == NULL)
		{
			fprintf(stderr, "error hzk16\n");
			return 1;
		}
		offset = (94 * (unsigned int)(Character[0] - 0xa0 - 1) + (Character[1] - 0xa0 - 1)) * 32;
		fseek(fphzk, offset, SEEK_SET);
		fread(buffer, 1, 32, fphzk);
		cout << endl;
		cout << "读取HZK16字库汉字编码"<<endl;
		for (k = 0; k < 16; k++)
		{
			for (j = 0; j < 2; j++) 
			{
				for (i = 0; i < 8; i++)
				{
					flag = buffer[k * 2 + j] & key[i];
					printf("%s", flag ? "●" : "○");
					temp1 = k * 16 + 8 * j + i;
					character[temp1] = flag ? 1 : 0;
				}
			}
			cout << endl;
		}
		fclose(fphzk);
		fphzk = NULL;
	}
	printf("\n");

	//扫描点阵获取子信息块
	k = 0;
	int a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0, g1 = 0, h1 = 0, i1 = 0, j1 = 0, k1 = 0, l1 = 0, mm = 0, n1 = 0, o1 = 0, p1 = 0;
	for (i = 0; i < 256;)
	{
		int temp[4] = { 0, 0, 0, 0 };
		temp[0] = character[i];
		temp[1] = character[i + 1];
		temp[2] = character[i + 16];
		temp[3] = character[i + 17];
		int tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m1[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[0] = freq[0] + 1; childid[k] = 'A'; a1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m2[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[1] = freq[1] + 1; childid[k] = 'B'; b1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m3[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[2] = freq[2] + 1; childid[k] = 'C'; c1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m4[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[3] = freq[3] + 1; childid[k] = 'D'; d1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m5[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[4] = freq[4] + 1; childid[k] = 'E'; e1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m6[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[5] = freq[5] + 1; childid[k] = 'F'; f1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m7[l]) { tflag++; }
		}
		if (tflag == 4) {
			freq[6] = freq[6] + 1; childid[k] = 'G'; g1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m8[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[7] = freq[7] + 1; childid[k] = 'H'; h1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m9[l]) { tflag++; }
		}
		if (tflag == 4) {
			freq[8] = freq[8] + 1; childid[k] = 'I'; i1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m10[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[9] = freq[9] + 1; childid[k] = 'J'; j1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m11[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[10] = freq[10] + 1; childid[k] = 'K'; k1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m12[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[11] = freq[11] + 1; childid[k] = 'L'; l1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m13[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[12] = freq[12] + 1; childid[k] = 'M'; mm++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m14[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[13] = freq[13] + 1; childid[k] = 'N'; n1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m15[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[14] = freq[14] + 1; childid[k] = 'O'; o1++;
		}
		tflag = 0;
		for (l = 0; l < 4; l++)
		{
			if (temp[l] == m16[l]) { tflag++; }
		}
		if (tflag == 4)
		{
			freq[15] = freq[15] + 1; childid[k] = 'P'; p1++;
		}
		i = i + 2;
		k++;
		if ((i % 16) == 0) { i = i + 16; }
	}
	
	
	int sum = 0;
	for (i = 0; i < 16; i++)
	{
		sum = sum + freq[i];
	}
	cout << endl;
	cout << "以字母A-P代表2X2点阵的16种情况" << endl;
	cout << "输出A-P出现的频次，依次为：" << a1 << " " << b1 << " " << c1 << " " << d1 << " " << e1 << " " << f1 << " " << g1 << " " << h1 << " " << i1 << " " << j1 << " " <<
		k1 << " " << l1 << " " << mm << " " << n1 << " " << o1 << " " << p1 << " " << endl;//A-P的出现的次数
	//扫描至此结束

	for (i = 0; i < 64; i++)
	{
		printf("%c ", childid[i]);
		if (i % 8 == 7) { printf("\n"); }
	}
	printf("\n");

	//编码过程
	const int n = 16;
	Node huffTree[2 * n];
	//用字母A-P代表2X2点阵的16种可能情况
	string str[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
	int w[] = { a1, b1, c1, d1, e1, f1, g1, h1, i1, j1, k1, l1, mm, n1, o1, p1 };
	Huff_Tree(huffTree, w, str, n);
	Huff_Code(huffTree, n);
	string codestr = "", codestrp = "";
	for (i = 0; i < 64; i++)
	{
		if (childid[i] == 'A') { codestr = codestr + huffTree[0].code; }
		if (childid[i] == 'B') { codestr = codestr + huffTree[1].code; }
		if (childid[i] == 'C') { codestr = codestr + huffTree[2].code; }
		if (childid[i] == 'D') { codestr = codestr + huffTree[3].code; }
		if (childid[i] == 'E') { codestr = codestr + huffTree[4].code; }
		if (childid[i] == 'F') { codestr = codestr + huffTree[5].code; }
		if (childid[i] == 'G') { codestr = codestr + huffTree[6].code; }
		if (childid[i] == 'H') { codestr = codestr + huffTree[7].code; }
		if (childid[i] == 'I') { codestr = codestr + huffTree[8].code; }
		if (childid[i] == 'J') { codestr = codestr + huffTree[9].code; }
		if (childid[i] == 'K') { codestr = codestr + huffTree[10].code; }
		if (childid[i] == 'L') { codestr = codestr + huffTree[11].code; }
		if (childid[i] == 'M') { codestr = codestr + huffTree[12].code; }
		if (childid[i] == 'N') { codestr = codestr + huffTree[13].code; }
		if (childid[i] == 'O') { codestr = codestr + huffTree[14].code; }
		if (childid[i] == 'P') { codestr = codestr + huffTree[15].code; }

	}
	cout << endl;
	cout << "哈夫曼编码如下："<<endl;
	std::cout << codestr << endl;
	cout << endl;
	//解码过程
	string decodes = Huff_Decode(huffTree, n, codestr);
	for (i = 0; i < 64; i++)
	{
		std::cout << decodes[i] << ' ';
		if (i % 8 == 7) { std::cout << endl; }
	}
	//还原原点阵
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (decodes[8 * i + j] == 'A') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'B') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'C') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'D') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'E') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'F') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'G') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'H') { dcharacter[2 * j + i * 32] = 0; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'I') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'J') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'K') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'L') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'M') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'N') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 0; dcharacter[2 * j + i * 32 + 17] = 1; }
			if (decodes[8 * i + j] == 'O') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 1; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 0; }
			if (decodes[8 * i + j] == 'P') { dcharacter[2 * j + i * 32] = 1; dcharacter[2 * j + i * 32 + 1] = 0; dcharacter[2 * j + i * 32 + 16] = 1; dcharacter[2 * j + i * 32 + 17] = 1; }

		}
	}
	cout << endl;
	std::cout << "原点阵码为(二进制)：" << endl;
	for (i = 0; i < 256; i++)
	{
		std::cout << dcharacter[i] << " ";
		if (i % 16 == 15) { std::cout << endl; }
	}
	cout << endl;
	cout << "输出点阵汉字" << endl;
	for (i = 0; i < 256; i++)
	{
		if (dcharacter[i] == 1) { cout << "●"; }
		if (dcharacter[i] == 0) { cout << "○"; }
		if (i % 16 == 15) { std::cout << endl; }
	}
	std::system("pause");
	return 0;
}