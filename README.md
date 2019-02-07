```cpp
class rwlock
{
public:
	rwlock(): read_cnt(0)
	{
                pthread_mutex_init(&read_mtx,NULL);
                pthread_mutex_init(&write_mtx,NULL);
	}

	~ rwlock()
	{
                pthread_mutex_destroy(&read_mtx);
                pthread_mutex_destroy(&write_mtx);
	}

	void readLock()
	{
		pthread_mutex_lock(&read_mtx);
		if (++read_cnt == 1)
			pthread_mutex_lock(&write_mtx);
		pthread_mutex_unlock(&read_mtx);
	}

	void readUnlock()
	{
		pthread_mutex_lock(&read_mtx);
		if (--read_cnt == 0)
			pthread_mutex_unlock(&write_mtx);
		pthread_mutex_unlock(&read_mtx);
	}

	void writeLock()
	{
		pthread_mutex_lock(&write_mtx);
	}

	void writeUnlock()
	{
		pthread_mutex_unlock(&write_mtx);
	}

private:
	pthread_mutex_t read_mtx;
	pthread_mutex_t write_mtx;
	int read_cnt; // 读锁个数
};
```
