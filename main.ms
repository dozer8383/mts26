init = function()
  checkRectMouseHover = function(x, y, width, height)
    local hover = true
    if mouse.x < (x - width/2) then hover = false end
    if mouse.x > (x + width/2) then hover = false end
    if mouse.y < (y - height/2) then hover = false end
    if mouse.y > (y + height/2) then hover = false end
    return hover
  end
  mtsRound = function(value)
    if value >= 1000000000000000000000 then
      value = round(value / 100000000000000000000)
      value = value/10 + " s"
    elsif value >= 1000000000000000000 then
      value = round(value / 100000000000000000)
      value = value/10 + " Q"
    elsif value >= 1000000000000000 then
      value = round(value / 100000000000000)
      value = value/10 + " q"
    elsif value >= 1000000000000 then
      value = round(value / 100000000000)
      value = value/10 + " t"
    elsif value >= 1000000000 then
      value = round(value / 100000000)
      value = value/10 + " b"
    elsif value >= 1000000 then
      value = round(value / 100000)
      value = value/10 + " m"
    end
    return value
  end
  hovertime = 0
  fade = 0
  introslide = 0
  year = 2000
  weather = 0
  money = 10
  ticks = 0
  income = 5
  if storage.get("hasPlayedBefore") == 0 then
    gamescreen = "intro"
    storage.set("hasPlayedBefore",1)
  else
    gamescreen = "title"
  end
  asset_manager.loadFont("playfairdisplayitalic")
  mouse.x = 0
  mouse.y = 0
end

update = function()
  parallaxX = 0-mouse.x/50
  parallaxY = 0-mouse.y/50
  if screen.isFontReady("playfairdisplayitalic") == false then
    fade = 0
  elsif gamescreen == "intro" then
    frame += 1
    if frame < 100 then
      introslide = 0
      fade += 0.01
    elsif frame > 200 and frame < 300 then
      fade += 0.01
    elsif frame > 400 and frame < 450 then
      fade = 0
      introslide = 1
    elsif frame > 450 and frame < 550 then
      fade += 0.01
    elsif frame > 550 and frame < 650 then
      fade += 0.01
    elsif frame > 750 and frame < 800 then
      fade = 0
      introslide = 2
    elsif frame > 800 and frame < 850 then
      fade += 0.02
    elsif frame > 850 then
      gamescreen = "title"
    end
  elsif gamescreen == "title" then
    if fade > 0 then
      fade -= 0.01
    end
    if checkRectMouseHover(screen.width/4+parallaxX,30+parallaxY,70,20) then
      hovertime += (60-hovertime)/5
      selection = 0
      if mouse.left then
        gamescreen = "game"
        fade = 1
      end
    elsif checkRectMouseHover(screen.width/4+parallaxX,parallaxY,70,20) then
      hovertime += (50-hovertime)/5
      selection = 1
    elsif checkRectMouseHover(screen.width/4+parallaxX,-30+parallaxY,70,20) then
      hovertime += (40-hovertime)/5
      selection = 2
    else
      hovertime += (0-hovertime)/5
    end
  elsif gamescreen == "game" then
    if fade > 0 then
      fade -= 0.02
    end
    ticks += 1
    if ticks % (10*60) == 0 then
      harvest = 1-harvest
      year += 1
    end
    if not showshop then
      if checkRectMouseHover(0+parallaxX,-80+parallaxY,30,30) then
        hovertime += (60-hovertime)/5
        if mouse.left and harvest then
          harvest = false
          money += income
        end
      elsif checkRectMouseHover(-30+parallaxX,-80+parallaxY,20,20) then
        hovertime += (50-hovertime)/5
        selection = 1
      elsif checkRectMouseHover(30+parallaxX,-80+parallaxY,20,20) then
        hovertime += (40-hovertime)/5
        if mouse.press and mouse.left then
          showshop = 1-showshop
        end
      else
        hovertime += (0-hovertime)/5
      end
    else
      if checkRectMouseHover((0-screen.width/2)+30+parallaxX,-80+parallaxY,20,20) and mouse.left then
        showshop = false
      end
    end
  end
end

draw = function()
  screen.clear("#2C3219")
  screen.setPixelated(0)
  screen.setFont("playfairdisplayitalic")
  if gamescreen == "title" then
    screen.setAlpha(1)
    screen.drawSprite("mts25sunny",mouse.x/100,mouse.y/100,screen.width+20)
    screen.drawSprite("mts25logo",0-screen.width/4+parallaxX,0+parallaxY,150)
    screen.drawText("(c) 2025 Jasper Games",0-screen.width/2+parallaxX+50,-80+parallaxY,5,"#E6E1CF")
    if hovertime > 0 then
      if selection == 0 then
        screen.fillRect(screen.width/4+parallaxX+hovertime/2-29,25+parallaxY,hovertime,2,"#2C3219")
      elsif selection == 1 then
        screen.fillRect(screen.width/4+parallaxX+hovertime/2-26,-5+parallaxY,hovertime,2,"#2C3219")
      elsif selection == 2 then
        screen.fillRect(screen.width/4+parallaxX+hovertime/2-23,-35.5+parallaxY,hovertime,2,"#2C3219")
      end
    end
    screen.setColor("#E6E1CF")
    screen.drawText("Start New",screen.width/4+parallaxX,30+parallaxY,10)
    screen.drawText("Continue",screen.width/4+parallaxX,parallaxY,10)
    screen.drawText("Settings",screen.width/4+parallaxX,-30+parallaxY,10)
    screen.setAlpha(max(0,fade))
    screen.fillRect(0,0,screen.width,screen.height,"#fff")
  elsif gamescreen == "intro" then
    if introslide == 0 then
      screen.setAlpha(fade)
      screen.drawSprite("jaspergameslogo",0,0,1042/10,134/10)
      screen.setAlpha(max(0,fade-1))
      screen.drawText("Presents",0,-17,6,"#A8B778")
    elsif introslide == 1 then
      screen.setAlpha(fade)
      screen.drawText("Money Tree Simulator",-10,0,7,"#fff")
      screen.setAlpha(max(0,fade-1))
      screen.drawText("2025",47,0,7,"#A8B778")
    elsif introslide == 2 then
      screen.setAlpha(fade)
      screen.fillRect(0,0,screen.width,screen.height,"#fff")
    end
  elsif gamescreen == "game" then
    if showshop then
      screen.setRotation(10)
      for y = -5 to 5
        for x = -5 to 5
          screen.drawSprite("checkeredloading",(x*49+parallaxX/2),y*50+parallaxY/2,50,50)
        end
      end
      screen.setRotation(0)
      screen.drawSprite("backicon",(0-screen.width/2)+30+parallaxX,-80+parallaxY,20)
    else
      screen.setAlpha(1)
      if harvest then
        if weather == 0 then
          screen.drawSprite("mts25sunnymoney",mouse.x/100,mouse.y/100,screen.width+20)
        elsif weather == 1 then
          screen.drawSprite("mts25rainymoney",mouse.x/100,mouse.y/100,screen.width+20)
        else 
          screen.drawSprite("mts25snowymoney",mouse.x/100,mouse.y/100,screen.width+20)
        end
      else
        if weather == 0 then
          screen.drawSprite("mts25sunny",mouse.x/100,mouse.y/100,screen.width+20)
        elsif weather == 1 then
          screen.drawSprite("mts25rainy",mouse.x/100,mouse.y/100,screen.width+20)
        else 
          screen.drawSprite("mts25snowy",mouse.x/100,mouse.y/100,screen.width+20)
        end
      end
      screen.setAlpha(1-fade)
      if harvest then
        screen.drawSprite("harveston",0+parallaxX,-80+parallaxY,30)
      else
        screen.drawSprite("harvestoff",0+parallaxX,-80+parallaxY,30)
      end
      screen.drawSprite("infoicon",-30+parallaxX,-80+parallaxY,20)
      screen.drawSprite("saveicon",-60+parallaxX,-80+parallaxY,20)
      screen.drawSprite("shopicon",30+parallaxX,-80+parallaxY,20)
      screen.drawText("$"+mtsRound(money),0+parallaxX,-50+parallaxY,15,"#fff")
      screen.drawText("Year "+year,0-screen.width/2+50+parallaxX,-80+parallaxY,10)
      
      screen.setAlpha(max(0,fade))
      screen.drawSprite("logo",0-screen.width/4+parallaxX,0+parallaxY,100)
      screen.drawSprite("copyright",0-screen.width/4+parallaxX,-70+parallaxY,80)
      if hovertime > 0 then
        if selection == 0 then
          screen.fillRect(screen.width/4+parallaxX+hovertime/2-33,25+parallaxY,hovertime,2,"#fff")
        elsif selection == 1 then
          screen.fillRect(screen.width/4+parallaxX+hovertime/2-28,-5+parallaxY,hovertime,2,"#fff")
        elsif selection == 2 then
          screen.fillRect(screen.width/4+parallaxX+hovertime/2-23,-33.5+parallaxY,hovertime,2,"#fff")
        end
      end
      screen.drawSprite("startnew",screen.width/4+parallaxX,30+parallaxY,70)
      screen.drawSprite("continue",screen.width/4+parallaxX,parallaxY,60)
      screen.drawSprite("settings",screen.width/4+parallaxX,-30+parallaxY,50)
    end
  end
end