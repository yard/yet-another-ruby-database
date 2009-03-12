# -*- coding: euc-jp -*-
require "tkcanvas"

def optionMenu(menubutton, varName, firstValue, *rest)
  varName.value = firstValue
  configoptions = {'textvariable'=>varName,'indicatoron'=>'on',
    'relief'=>'raised','borderwidth'=>2,'highlightthickness'=>2,
    'anchor'=>'c','direction'=>'flush'}
  configoptions.each {|key, value|
    menubutton.configure(key, value)
  }
  menu = TkMenu.new(menubutton) {
    tearoff 'off'
    add 'radio', 'label'=>firstValue, 'variable'=>varName
  }
  menubutton.menu(menu)
  for i in rest
    menu.add 'radio', 'label'=>i, 'variable'=>varName
  end
  
  return menu
end

if defined?($menubu_demo) && $menubu_demo
  $menubu_demo.destroy
  $menubu_demo = nil
end

$menubu_demo = TkToplevel.new {|w|
  title("Menu Button Demonstration")
  iconname("menubutton")
}

positionWindow($menubu_demo)

# version check
if $tk_version.to_f < 8.0

# label ����
TkLabel.new($menubu_demo,'font'=>$font,'wraplength'=>'4i','justify'=>'left') {
    text("�¹Ԥ��褦�Ȥ���������ץȤ� Tk8.0 �ʾ�����ѤǤ��뵡ǽ�����Ѥ��Ƥ��뤿�ᡢ���ʤ��� Ruby#{VERSION}/Tk#{$tk_version}#{(Tk::JAPANIZED_TK)? 'jp': ''} �Ǥ�����˼¹ԤǤ��ޤ��󡣤�äƥǥ�μ¹Ԥ���ߤ��ޤ����������������Υ����ɻ��ȥܥ���򲡤����Ȥǡ��¹Ԥ���ߤ��줿������ץȤΥ������򻲾Ȥ��뤳�Ȥϲ�ǽ�Ǥ���")
}.pack('side'=>'top')

# frame ����
TkFrame.new($menubu_demo) {|frame|
  TkButton.new(frame) {
    #text 'λ��'
    text '�Ĥ���'
    command proc{
      tmppath = $menubu_demo
      $menubu_demo = nil
      tmppath.destroy
    }
  }.pack('side'=>'left', 'expand'=>'yes')

  TkButton.new(frame) {
    text '�����ɻ���'
    command proc{showCode 'menubu'}
  }.pack('side'=>'left', 'expand'=>'yes')
}.pack('side'=>'bottom', 'fill'=>'x', 'pady'=>'2m')

else ; # Tk8.x

body = TkFrame.new($menubu_demo)
body.pack('expand'=>'yes', 'fill'=>'both')

below = TkMenubutton.new(body) {
  text "Below"
  underline 0
  direction 'below'
  relief 'raised'
}
belowMenu = TkMenu.new(below) {
  tearoff 0
  add 'command', 'label'=>"Below menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Below menu.\""}
  add 'command', 'label'=>"Below menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Below menu.\""}
}
below.menu(belowMenu)
below.grid('row'=>0, 'column'=>1, 'sticky'=>'n')

below = TkMenubutton.new(body) {
  text "Below"
  underline 0
  direction 'below'
  relief 'raised'
}
belowMenu = TkMenu.new(below) {
  tearoff 0
  add 'command', 'label'=>"Below menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Below menu.\""}
  add 'command', 'label'=>"Below menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Below menu.\""}
}
below.menu(belowMenu)
below.grid('row'=>0, 'column'=>1, 'sticky'=>'n')

below = TkMenubutton.new(body) {
  text "Below"
  underline 0
  direction 'below'
  relief 'raised'
}
belowMenu = TkMenu.new(below) {
  tearoff 0
  add 'command', 'label'=>"Below menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Below menu.\""}
  add 'command', 'label'=>"Below menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Below menu.\""}
}
below.menu(belowMenu)
below.grid('row'=>0, 'column'=>1, 'sticky'=>'n')

right = TkMenubutton.new(body) {
  text "Right"
  underline 0
  direction 'right'
  relief 'raised'
}
rightMenu = TkMenu.new(right) {
  tearoff 0
  add 'command', 'label'=>"Right menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Left menu.\""}
  add 'command', 'label'=>"Right menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Right menu.\""}
}
right.menu(rightMenu)
right.grid('row'=>1, 'column'=>0, 'sticky'=>'w')

left = TkMenubutton.new(body) {
  text "Left"
  underline 0
  direction 'left'
  relief 'raised'
}
leftMenu = TkMenu.new(left) {
  tearoff 0
  add 'command', 'label'=>"Left menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Left menu.\""}
  add 'command', 'label'=>"Left menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Left menu.\""}
}
left.menu(leftMenu)
left.grid('row'=>1, 'column'=>2, 'sticky'=>'e')

center = TkFrame.new(body) {
  grid('row'=>1, 'column'=>1, 'sticky'=>'news')
}

above = TkMenubutton.new(body) {
  text "Above"
  underline 0
  direction 'above'
  relief 'raised'
}
aboveMenu = TkMenu.new(above) {
  tearoff 0
  add 'command', 'label'=>"Above menu: first item", 'command'=>proc {puts "\"You have selected the first item from the Above menu.\""}
  add 'command', 'label'=>"Above menu: second item", 'command'=>proc {puts "\"You have selected the second item from the Above menu.\""}
}
above.menu(aboveMenu)
above.grid('row'=>2, 'column'=>1, 'sticky'=>'s')

center = TkFrame.new(body) {
  grid('row'=>1, 'column'=>1, 'sticky'=>'news')
}

TkFrame.new($menubu_demo) {|frame|
  TkButton.new(frame) {
    #text 'λ��'
    text '�Ĥ���'
    command proc {
      tmppath = $menubu_demo
      $menubu_demo = nil
      tmppath.destroy
    }
  }.pack('side'=>'left', 'expand'=>'yes')

  TkButton.new(frame) {
    text '�����ɻ���'
    command proc { showCode 'menubu' }
  }.pack('side'=>'left', 'expand'=>'yes')
}.pack('side'=>'bottom', 'expand'=>'yes', 'fill'=>'x', 'pady'=>'2m')

msg = TkLabel.new(center) {
#  font $font
  wraplength '4i'
  justify 'left'
  text "����ϥ�˥塼�ܥ���Υǥ�Ǥ���\"Below\"�Υܥ����\
���˥�˥塼��Ф���\"Right\"�Υܥ���ϱ��˥�˥塼��Ф��ơ�\
�ġĤȤʤ�ޤ�������ʸ�Ϥβ��ˤ�2�ĤΥ��ץ�����˥塼������ޤ���\
1�Ĥ����̤Υ�˥塼�ǡ��⤦1�Ĥ�16���Υѥ�åȤǤ���"
}
msg.pack('side'=>'top', 'padx'=>25, 'pady'=>25)

TkFrame.new(center) {|f|
  menubuttonoptions = TkVariable.new
  mbutton = TkMenubutton.new(f)
  options = optionMenu(mbutton, menubuttonoptions, 
                       'one', 'two', 'three')
  mbutton.pack('side'=>'left', 'padx'=>25, 'pady'=>25)
  paletteColor = TkVariable.new
  colors = ['Black','red4','DarkGreen','NavyBlue', 'gray75',
    'Red','Green','Blue','gray50','Yellow','Cyan','Magenta',
    'White','Brown','DarkSeaGreen','DarkViolet']
  colorMenuButton = TkMenubutton.new(f)
  m = optionMenu(colorMenuButton, paletteColor, *colors)
  begin
    windowingsystem = Tk.windowingsystem()
  rescue
    windowingsystem = ""
  end
  if windowingsystem == "classic" || windowingsystem == "aqua"
    topBorderColor = 'Black'
    bottomBorderColor = 'Black'
  else
    topBorderColor = 'gray50'
    bottomBorderColor = 'gray75'
  end
  for i in 0..15
    image = TkPhotoImage.new('height'=>16, 'width'=>16)
    image.put(topBorderColor, 0, 0, 16, 1)
    image.put(topBorderColor, 0, 1, 1, 16)
    image.put(bottomBorderColor, 0, 15, 16, 16)
    image.put(bottomBorderColor, 15, 1, 16, 16)
    image.put(colors[i], 1, 1, 15, 15)

    selectimage = TkPhotoImage.new('height'=>16, 'width'=>16)
    selectimage.put('Black', 0, 0, 16, 2)
    selectimage.put('Black', 0, 2, 2, 16)
    selectimage.put('Black', 2, 14, 16, 16)
    selectimage.put('Black', 14, 2, 16, 14)
    selectimage.put(colors[i], 2, 2, 14, 14)

    m.entryconfigure(i, 'image'=>image, 'selectimage'=>selectimage, 'hidemargin'=>'on')
  end
  m.configure('tearoff', 'on')
  for c in ['Black', 'gray75', 'gray50', 'White']
    m.entryconfigure(c, 'columnbreak'=>1)
  end
  colorMenuButton.pack('side'=>'left', 'padx'=>25, 'pady'=>25)
  pack 'padx'=>25, 'pady'=>25
}

end ; # Tk8.x