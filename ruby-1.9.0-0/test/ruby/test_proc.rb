require 'test/unit'

class TestProc < Test::Unit::TestCase
  def test_proc
    p1 = proc{|i| i}
    assert_equal(2, p1.call(2))
    assert_equal(3, p1.call(3))

    p1 = proc{|i| i*2}
    assert_equal(4, p1.call(2))
    assert_equal(6, p1.call(3))

    p2 = nil
    x=0

    proc{
      iii=5				# nested local variable
      p1 = proc{|i|
        iii = i
      }
      p2 = proc {
        x = iii                 	# nested variables shared by procs
      }
      # scope of nested variables
      assert(defined?(iii))
    }.call
    assert(!defined?(iii))		# out of scope

    loop{iii=5; assert(eval("defined? iii")); break}
    loop {
      iii = 10
      def self.dyna_var_check
        loop {
          assert(!defined?(iii))
          break
        }
      end
      dyna_var_check
      break
    }
    p1.call(5)
    p2.call
    assert_equal(5, x)
  end

  def assert_arity(n)
    meta = class << self; self; end
    meta.class_eval {define_method(:foo, Proc.new)}
    assert_equal(n, method(:foo).arity)
  end

  def test_arity
    assert_equal(0, proc{}.arity)
    assert_equal(0, proc{||}.arity)
    assert_equal(1, proc{|x|}.arity)
    assert_equal(2, proc{|x, y|}.arity)
    assert_equal(-2, proc{|x, *y|}.arity)
    assert_equal(-1, proc{|*x|}.arity)
    assert_equal(-1, proc{|*|}.arity)
    assert_equal(-3, proc{|x, *y, z|}.arity)
    assert_equal(-4, proc{|x, *y, z, a|}.arity)

    assert_arity(0) {}
    assert_arity(0) {||}
    assert_arity(1) {|x|}
    assert_arity(2) {|x, y|}
    assert_arity(-2) {|x, *y|}
    assert_arity(-3) {|x, *y, z|}
    assert_arity(-1) {|*x|}
    assert_arity(-1) {|*|}
  end

  def m(x)
    lambda { x }
  end

  def test_eq
    a = m(1)
    b = m(2)
    assert_not_equal(a, b, "[ruby-dev:22592]")
    assert_not_equal(a.call, b.call, "[ruby-dev:22592]")

    assert_not_equal(proc {||}, proc {|x,y|}, "[ruby-dev:22599]")

    a = lambda {|x| lambda {} }.call(1)
    b = lambda {}
    assert_not_equal(a, b, "[ruby-dev:22601]")
  end

  def test_block_par
    assert_equal(10, Proc.new{|&b| b.call(10)}.call {|x| x})
    assert_equal(12, Proc.new{|a,&b| b.call(a)}.call(12) {|x| x})
  end

  def test_safe
    safe = $SAFE
    c = Class.new
    x = c.new

    p = proc {
      $SAFE += 1
      proc {$SAFE}
    }.call
    assert_equal(safe, $SAFE)
    assert_equal(safe + 1, p.call)
    assert_equal(safe, $SAFE)

    c.class_eval {define_method(:safe, p)}
    assert_equal(safe, x.safe)
    assert_equal(safe, x.method(:safe).call)
    assert_equal(safe, x.method(:safe).to_proc.call)

    p = proc {$SAFE += 1}
    assert_equal(safe + 1, p.call)
    assert_equal(safe, $SAFE)

    c.class_eval {define_method(:inc, p)}
    assert_equal(safe + 1, proc {x.inc; $SAFE}.call)
    assert_equal(safe, $SAFE)
    assert_equal(safe + 1, proc {x.method(:inc).call; $SAFE}.call)
    assert_equal(safe, $SAFE)
    assert_equal(safe + 1, proc {x.method(:inc).to_proc.call; $SAFE}.call)
    assert_equal(safe, $SAFE)
  end

  def m2
    "OK"
  end

  def block
    method(:m2).to_proc
  end

  # [yarv-dev:777] block made by Method#to_proc
  def test_method_to_proc
    b = block()
    assert_equal "OK", b.call
  end

end
