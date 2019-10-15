#include <functional>
#include <string>
#include <vector>

using namespace std;


class Test
{
public:
    Test(string, function<bool()>);
   
    bool run()
    {
        if(not toRun())
        {
            cout << "Test '" << testName << "' failed" << endl;
            return false;
        }
        else
        {
            cout << "Test '" << testName << "' passed" << endl;
        }
        
        return true;
    }
private:
    function<bool()> toRun;
    string testName;
};


Test::Test(string p_testName, function<bool()> p_toRun) :
        toRun(p_toRun), testName(p_testName)
    {
    }

