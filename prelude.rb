
# Mutex

class Mutex
  def synchronize
    self.lock
    begin
      yield
    ensure
      self.unlock
    end
  end
end

# Thread

class Thread
  MUTEX_FOR_THREAD_EXCLUSIVE = Mutex.new
  def self.exclusive
    MUTEX_FOR_THREAD_EXCLUSIVE.synchronize{
      yield
    }
  end
end

