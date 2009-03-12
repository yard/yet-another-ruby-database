start_yard

class Klass
  def initialize(a, b)
    @a, @b = a, b
  end
end

$a = [1,2,3]
$a << Klass.new(1,1)

p $a.yard_id
p $a.last.yard_id

$b = [$a]

p $a.yard_id
p $a.last.yard_id
p $b.yard_id

