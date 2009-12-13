require 'test/unit'
require 'continuation'
require 'fiber'

class TestContinuation < Test::Unit::TestCase
  def test_create
    assert_equal(:ok, callcc{:ok})
    assert_equal(:ok, callcc{|c| c.call :ok})
  end

  def test_call
    assert_equal(:ok, callcc{|c| c.call :ok})

    ary = []
    ary << callcc{|c|
      @cont = c
      :a
    }
    @cont.call :b if ary.length < 3
    assert_equal([:a, :b, :b], ary)
  end

  def test_check_localvars
    vv = 0
    @v = 0
    @ary = []
    [1, 2, 3].each{|i|
      callcc {|k| @k = k}
      @v += 1
      vv += 1
    }
    @ary << [vv, @v]
    @k.call if @v < 10
    assert_equal((3..10).map{|e| [e, e]}, @ary)
  end

  def test_error
    cont = callcc{|c| c}
    assert_raise(RuntimeError){
      Thread.new{cont.call}.join
    }
    assert_raise(LocalJumpError){
      callcc
    }
    assert_raise(RuntimeError){
      c = nil
      Fiber.new do
        callcc {|c2| c = c2 }
      end.resume
      c.call
    }
  end
end

