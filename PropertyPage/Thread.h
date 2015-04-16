#pragma  once 

namespace pp{

class IRunable
{
public:
	virtual ~IRunable() {} ;
	virtual UINT Run() = 0;

protected:
	IRunable() {};
};


class Thread : public IRunable
{
public:
	Thread();
	~Thread();
	virtual UINT Run();
	void Initialize();
	BOOL StartThread();

	static UINT AFX_CDECL ThreadFunc(LPVOID pParam);

public:
	int		m_nID;
private:
	CWinThread*  m_pThread;
};

} // namespace pp