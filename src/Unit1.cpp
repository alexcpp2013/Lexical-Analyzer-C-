//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused

#include <stdio.h>
#include <io.h>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

//------------------------------------------------------------------------------------

const int countKeyWords = 65;

//������� �������� �����(������):
string keyWords[ ] = {  "for",       "while",     "do",       "foreach",  "break",
                        "continue",  "return",    "switch",   "case",     "default",
                        "if",        "else",      "int",      "char",     "bool",
                        "decimal",   "long",      "struct",   "object",   "string",
                        "class",     "interface", "delegate", "public",   "private",
                        "protected", "internal",  "new",      "static",   "virtual",
                        "override",  "extern",    "null",     "sizeof",   "namespace",
                        "using",     "get",       "set",      "float",    "double",
                        "void",      "as",        "is",       "sbyte",    "short",
                        "byte",      "uint",      "ushort",   "ulong",    "signed",
                        "unsigned",  "readonly",  "const",    "volatile", "abstract",
                        "sealed",    "try",       "catch",    "finally",  "throw",
                        "ref",       "out",       "true",     "false",    "decimal"
                };


const int countDelimiters = 14;

//������� �����������:
unsigned char delimiters[ ] = { ' ', ';', '(', ')', ',',
                                '{', '}', '\n', '\t', '\r',
                                '"', '[', ']', ':'
                        };

//------------------------------------------------------------------------

bool KeywordCheck( const string &lexem ); //�������� �� �������� �����
void DelimiterCheck( const string &lexem );//�������� �� �����������
bool DigitCheck( const string &lexem, const unsigned long &delimpos );//�������� �� �����
bool IdentifierCheck( const string &lexem, const unsigned long &delimpos, const unsigned char &next );//�������� �� �������������
bool ComplexOperatorCheck( const unsigned char &delim, const unsigned char &next );//�������� �� ��������� ��������*
void GetToken( const string &lexem, const unsigned long &delimpos, const unsigned char &next ); //�������� �����

//-----------------------------------------------------------------------------------------------

//�������� �����:
void GetToken( const string &lexem, const unsigned long &delimpos, const unsigned char &next )
{

        if ( !KeywordCheck( lexem ) ) //�������� �� �������� �����
	{
                if ( !IdentifierCheck( lexem, delimpos, next ) ) //�������� �� �������������
		DigitCheck( lexem, delimpos ); //�������� �� �����
	}

}

//---------------------------------------------------------------------------------------------------

//�������� �������� �� �������� �����:
bool KeywordCheck( const string &lexem )
{

        for ( int i = 0; i != countKeyWords; ++i )
	{
		if ( lexem == keyWords[ i ] ) //�������� �����
		{
			cout << "Keyword: " << keyWords[ i ] << "\n";
			return true;
		}
	}
	return false;

}

//--------------------------------------------------------------------------------------------------------

//�������� �� ����������� � ���������:
void DelimiterCheck( const unsigned char &symbol )
{

        //�������� ���������:
        unsigned char operators[ ] = {  '+', '-', '=', '/', '*', '>', '<', '~', '!', '|',
                                        '&', '%'
                                };
                                
	for ( int i = 0; i != countDelimiters; ++i )
	{
		if ( symbol == delimiters[ i ] ) //�����������
		{
			cout << "Delimeter: " << symbol << "\n";
		}
		else
                {
		        if ( symbol == operators[ i ] ) //��������
		        {
			        cout << "Operator: " << symbol << "\n";
		        }
                }
	}

}

//--------------------------------------------------------------------------------------

//�������� �� �������������� � ������:
bool DigitCheck( const string &lexem, const unsigned long &delimpos )
{

	unsigned int i = 0;
	while ( i < delimpos )  //�� ������� �����������
	{
		if ( !isdigit( lexem[ i ] ) ) //�� �����
		{
			cout << "Error1!: " << lexem << "\n";
			return false;
		}
		++i;
	}
	cout << "Number: " << lexem << "\n";
	return true;

}

//-----------------------------------------------------------------------------------------------

//�������� �� �������������� � �������:
bool IdentifierCheck( const string &lexem, const unsigned long &delimpos, const unsigned char &next )
{

	if ( isalpha( lexem[ 0 ] ) || ( lexem[ 0 ] == '_' ) ) //�����
	{
		for ( unsigned int i = 1; i < delimpos; ++i ) //����� �����������
		{
			if ( isalnum( lexem[ i ] ) || ( lexem[ i ] == '_' ) ) //���������-�������� ���
                        {
                                ;
                        }
			else return false;
		}
		if ( next == '(' )
		{
			cout << "Function: " << lexem << '\n';
		}
		else
		{
			cout << "Identificator: " << lexem << '\n';
		}
		return true;
	}
	/*else
	{
		cout << "Error2!: " << lexem << "\n";
	}*/
	return false;

}

//------------------------------------------------------------------------------------------------

//�������� �� ��������� ���������(���������, ����������, ������, �����):
bool ComplexOperatorCheck( const unsigned char &delim, const unsigned char &next )
{

	if ( next == '=' )
	{
		if ( delim == '=' || delim == '<' || delim == '>' || delim == '!' )
		{
			cout << "Compare operator: " << delim << next << '\n';
			return true;
		}
		else
		if ( delim == '+' || delim == '-' )
		{
			cout << "Arifmatic operator: " << delim << next << '\n';
			return true;
		}
	}
	else
	if ( ( delim == '&' && next == '&' ) || ( delim == '|' && next == '|' ) )
	{
		cout << "Logic operator: " << delim << next << '\n';
		return true;
	}
	else
	if ( ( delim == '<' && next == '<' ) || ( delim == '>' && next == '>' ) )
	{
		cout << "Shift operator: " << delim << next << '\n';
		return true;
	}
	else
	if ( ( delim == '+' && next == '+' ) || ( delim == '-' && next == '-' ) )
	{
		cout << "Arifmatic operator: " << delim << next << '\n';
		return true;
	}
	return false;

}

//------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{

	string s;//������ ��� ����������� �����
	unsigned long size = 0;//��� ������� �����
	FILE *f;

	if ( ( f = fopen( "test.cs", "rt" ) ) != NULL )//������� ����
	{
		size = filelength( fileno( f ) );//������� ��� ������ ����� handle �����
		s.resize( size );//������� ������ ������ ��������������� �����
		fread( &s[ 0 ], 1, size, f );//������� � ������

                cout << "\n-------------------------------Input file-------------------------------------\n\n";
                cout << s;
		cout << "\n-------------------------------Start------------------------------------------\n\n";

		const string delim = " ;(),.{}[]\n\t\r+-=/*><~!|&%:\"";
		long delimpos = s.find_first_of( delim, 0 );//������� �����������  //unsigned
		unsigned long begpos = 0;//������ ���������� �������

		while( delimpos != string :: npos ) //���������� ��������� ������ � ������������������ -1, � 0 ���������� ������
		{
                        //�������� �� �����������:
			if ( s[ delimpos ] == '/' )
			{
				if ( s[ delimpos + 1 ] == '/' )
				{
					unsigned long pos = delimpos;
					delimpos = s.find_first_of( "\n", delimpos + 1 );//���� ����� ������
					cout << "Coment: " << s.substr( pos, delimpos - pos ) << '\n';
					begpos = delimpos + 1;//���� ��������� �������
					delimpos = s.find_first_of( delim, delimpos + 1 );//��������� �����������
				}
				else
				if ( s[ delimpos + 1 ] == '*' )
				{
					unsigned long pos = delimpos;
					delimpos = s.find_first_of( "*", delimpos + 2 );//������ ������ ���������
					while ( s[ delimpos + 1 ] != '/')//���������
					{
						if ( delimpos == string :: npos )
						{
							cout << "Error3!: */ missed!\n";
							exit( 2 );
						}
                                                //�������� ������� ������� ������� �������� ������������
						delimpos = s.find_first_of( "*", delimpos + 1 );
					}
					cout << "Coment: " << s.substr( pos, delimpos - pos + 2 ) << '\n';
					begpos = delimpos + 2;//�� ������ ����� �������
					delimpos = s.find_first_of( delim, delimpos + 2 );//���� ������ �����������
				}
			}
			
                        //�������� �� �������������� ���������� ������:
			if ( s[ delimpos ] == '"' )
			{
				unsigned long pos = delimpos + 1;
				while (s[ delimpos = s.find_first_of( delim, delimpos + 1 ) ] != '"' )//���� �������� ������
				{
					if ( delimpos == string :: npos )
					{
						cout << "Error4!: \" missed!\n";
						exit( 2 );
					}
				}
				cout << "String: " << s.substr( pos, delimpos - pos ) << '\n';
				begpos = delimpos + 1;//��������� � ��������� �������
				delimpos = s.find_first_of( delim, delimpos + 1 );//���� �����������
			}

                        //�������� �� ����������� ���������:
			if ( ComplexOperatorCheck( s[ delimpos ], s[ delimpos + 1 ] ) )
			{
				delimpos = s.find_first_of( delim, delimpos + 1 );//���� �����������
				begpos = delimpos + 1;//��������� � �������
				delimpos = s.find_first_of( delim, begpos );//�� ���� ������ ����� �������
			}

                        //�����������:
			if (delimpos - begpos)
			GetToken( s.substr( begpos, delimpos - begpos ), delimpos - begpos, s[ delimpos ] );//�������� �����
			
			DelimiterCheck( s[ delimpos ] );//���� �����������
			begpos = delimpos + 1;//�� ������ ����� �������
			delimpos = s.find_first_of( delim, begpos );//�� ���� ������
		}

		fclose( f );
	}

	getchar( );
	return 0;
        
}

//----------------------------------------------------------------------------


