require 'test/unit'
begin
  require 'io/nonblock'
rescue LoadError
end

Thread.abort_on_exception = true
class TestIONonblock < Test::Unit::TestCase
  def test_flush
    r,w = IO.pipe
    w.nonblock = true
    w.sync = false
    w << "b"
    w.flush
    w << "a" * 4096
    Thread.new {
      Thread.pass
      w.close
    }
    result = ""
    t = Thread.new {
      while (Thread.pass; s = r.read(4096))
        result << s
      end
    }
    w.flush # assert_raise(IOError, "[ruby-dev:24985]") {w.flush}
    assert_nothing_raised {t.join}
    assert_equal(4097, result.size)
  end
end if IO.method_defined?(:nonblock)
