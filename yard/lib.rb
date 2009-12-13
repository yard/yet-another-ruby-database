class Stuff
  def initialize(name)
    @name = name
    @time = Time.now
  end
end

def lol(n)
  t = Time.now
  $c = []
  n.times { |i| $c << Stuff.new("item#{i}") }
  Time.now - t
end

Str = Struct.new(:a, :b, :c, :d)

start_yard