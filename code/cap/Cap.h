namespace cap
{
extern bool CapeActive_;

class Cap;
typedef Cap *cap_t;
extern cap_t cap_;
cap_t Cap_();

class Cap
{
public:
	Cap();
	~Cap();

	void Draw();
};


typedef void CAPTEST;

CAPTEST TestFindScripts();
} // namespace cap