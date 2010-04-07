#pragma once


class PB_EXPORT RpcUrl
{
public:
	RpcUrl(){ host = anyHost; path = ""; }
	RpcUrl(const RpcUrl &other)
	{
		*this = other;
	}
	static const char *anyHost;

	RpcUrl(const QString &p,const QString &h=anyHost){host=h;path=p;}
	RpcUrl &operator=(const RpcUrl &other)
	{
		host = other.host;
		path = other.path;
		return *this;
	}
	bool parse(QString  &s)
	{
		int i = s.indexOf("/");
		if(i<0)
		{
			host=anyHost;
			path=s;
		}else
		{
			host=s.left(i);
			path=s.mid(i+1);
		}
		return true;
	}
	bool match(const RpcUrl &mask) const
	{
		if(host!=mask.host && mask.host!=anyHost)
			return false;
		if(path!=mask.path)
			return false;
		return true;
	}
	
	bool isEmpty() const { return path.isEmpty(); }

	bool operator==(const RpcUrl &other) const
	{
		return host==other.host && path==other.path;
	}
	bool operator<(const RpcUrl &other) const
	{
		return toString()<other.toString();
	}

	RpcUrl &setPath(const QString &aPath){ path= aPath; return *this;}

	void clear(){ host = ""; path = ""; }
	QString toString() const{return host+"/"+path;}

	static RpcUrl remote(QString path);

public:
	QString host;
	QString path;
};


class PB_EXPORT RpcMethod : public RpcUrl
{
public:
	RpcMethod(){ }
	RpcMethod(const RpcMethod &other)
	{
		*this = other;
	}

	RpcMethod(const RpcUrl &other, const QString &m)
	{
		*static_cast<RpcUrl*>(this) = other;
		method = m;
	}

	RpcMethod &operator=(const RpcMethod &other)
	{
		RpcUrl::operator=(other);
		method = other.method;
		return *this;
	}

	bool operator==(const RpcMethod &other)
	{
		return RpcUrl::operator==(other) && method == other.method;
	}

public:
	QString method;
};
