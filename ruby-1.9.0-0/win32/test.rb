start_yard

class Klass
  def initialize(a, b)
    @a, @b = a, b
  end
end

a = {}

i =  Klass.new 4, 4

a[1] = Klass.new(1,1)
a[2] = Klass.new(2,2)
a[i] = Klass.new(3,3)

p "+" * 100

$d

$a = a

p $a.yard_id
$a.values.each { |x| p x.yard_id }
p i.yard_id

