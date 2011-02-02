#include "cppunitlite.h"
#include <string.h>
class TreeNode
{
public:
	TreeNode()
	{
		memset(this,0,sizeof(*this));
	}
	TreeNode* m_pLeft;
	TreeNode* m_pRight;
	int m_nValue;
};

int main()
{
	TestResult tr;
	TestRegistry::runAllTests(tr);
	return 1;	
}