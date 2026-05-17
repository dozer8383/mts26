init = function()
  print("Money Tree Simulator 2023")
  print("(c) " + (1970 + floor(system.time() / 31536000000)) + " Jasper Games")
  connection = new ServerConnection()
  asset_manager.loadFont("playfairdisplaysemibold")
  asset_manager.loadFont("poppinssemibold")
  game = object
    name = "New Farm"
    year = 1999
    perclick = 5
    perseason = 0
    trees = 1
    money = 10
    season = 0
    repellant = 0
    largestsum = 0
    costs = object
      tree = 15
      repellant = 3
      fertilizer = 200
      worker = 1000
    end
    display = object
      tree = "15"
      repellant = "3"
      fertilizer = "200"
      worker = "1000"
      money = "10"
    end
    ver = 0
    gen = 0
  end
  transition = object
    active = 0
    activate = function(color, gstateto, ostateto, speed)
      transition.color = color
      transition.alpha = 0
      transition.active = 1
      transition.speed = speed/60
      transition.gstateto = gstateto
      transition.ostateto = ostateto
    end
    update = function()
      if transition.alpha != 1 then
        if transition.active == 1 then transition.alpha += transition.speed end
        if transition.active == -1 then transition.alpha -= transition.speed end
      end
      if transition.alpha >= 1 then
        gamestate = transition.gstateto
        onlinestate = transition.ostateto
        transition.active = -1
      end
      if transition.alpha <= 0 and transition.active == -1 then
        transition.alpha = 0
        transition.active = 0
      end
    end
  end
  timer = 60*3
  seasons = [
    "spring",
    "summer",
    "autumn",
    "winter"
  ]
  gamestate = 0
  checkRectMouseHover = function(x, y, width, height)
    local hover = true
    if mouse.x < (x - width/2) then hover = false end
    if mouse.x > (x + width/2) then hover = false end
    if mouse.y < (y - height/2) then hover = false end
    if mouse.y > (y + height/2) then hover = false end
    return hover
  end
  rightAlign = screen.width / 2
  leftAlign = 0 - (screen.width / 2)
  moneyRound = function(value)
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
      value = value/10 + " T"
    elsif value >= 1000000000 then
      value = round(value / 100000000)
      value = value/10 + " B"
    elsif value >= 1000000 then
      value = round(value / 100000)
      value = value/10 + " M"
    end
    return value
  end
end

update = function()
  transition.update()
  if gamestate == 1 then
    game.display.tree = moneyRound(game.costs.tree)
    game.display.repellant = moneyRound(game.costs.repellant)
    game.display.fertilizer = moneyRound(game.costs.fertilizer)
    game.display.worker = moneyRound(game.costs.worker)
    game.display.money = moneyRound(game.money)
    if timer < 1 then
      timer = 60*2
      game.season += 1
      if moneybugattack == 1 then
        moneybugattack = 0
      end
      if random.nextInt(100) < 5 then
        moneybugattack = 1
      end
      if moneybugattack == 1 then
        if game.repellant > 0 then
          game.repellant -= 1
        else
          moneytime = 0
          game.trees = round(game.trees/1.05)
        end
      end
      game.money += game.perseason*game.perclick
      userdata.money = game.largestsum
      // system.javascript("this.encodedURI = `https://leaderboard.jmeow.net/moneytreesim2023/set/?name=${encodeURIComponent(player.runtime.vm.context.global.userdata.username)}&score=${encodeURIComponent(player.runtime.vm.context.global.userdata.money)}`")
      // request.get(encodedURI)
      // connection.send(userdata)
    else
      timer -= 1 
    end
    if game.season > 3 then
      game.season = 0
      game.year += 1
      if moneytime == 0 then
        moneytime = 1
      else
        moneytime = 0
      end
    end
    if checkRectMouseHover(0,0,150,150) and mouse.left and moneytime == 1 then
      game.money += game.perclick * game.trees
      moneytime = 0
    end
    if keyboard.press.SPACE and moneytime == 1 then
      game.money += game.perclick * game.trees
      moneytime = 0
    end
    if checkRectMouseHover(0,-80,100,30) and mouse.left and moneytime == 1 then
      game.money += game.perclick * game.trees
      moneytime = 0
    end
    if checkRectMouseHover(leftAlign + 40, 80, 70, 30) and mouse.press then
      system.javascript("this.JSONgame = JSON.stringify(player.runtime.vm.context.global.game)")
      encodedgame = base64.encode(JSONgame)
      system.file.save( encodedgame, game.name )
    end
    if checkRectMouseHover(rightAlign-60,80,60,30) and mouse.press then
      if shopopen == 1 then
        shopopen = 0
      else
        shopopen = 1
      end
    end
    if checkRectMouseHover(leftAlign + 110, 80, 60, 30) and mouse.press then
      if help == 1 then
        help = 0
      else
        help = 1
      end
    end
    if shopopen == 1 then
      if checkRectMouseHover(rightAlign - 60, 50, 100, 15) and mouse.press or keyboard.press.N then
        if game.money >= game.costs.tree then
          game.trees += 1
          game.money -= game.costs.tree
          game.costs.tree *= 1.035
          game.costs.tree = round(game.costs.tree)
        end
      end
      if checkRectMouseHover(rightAlign - 60, 30, 100, 15) and mouse.press or keyboard.press.M then
        if game.money >= game.costs.repellant then
          game.repellant += 1
          game.money -= game.costs.repellant
          game.costs.repellant += 1
          game.costs.repellant = round(game.costs.repellant)
        end
      end
      if checkRectMouseHover(rightAlign - 60, 10, 100, 15) and mouse.press or keyboard.press.F then
        if game.money >= game.costs.fertilizer then
          game.perclick *= 1.5
          game.money -= game.costs.fertilizer
          game.costs.fertilizer *= 1.7
          game.costs.fertilizer = round(game.costs.fertilizer)
          game.perclick = round(game.perclick)
        end
      end
      if checkRectMouseHover(rightAlign - 60, -10, 100, 15) and mouse.press or keyboard.press.H then
        if game.money >= game.costs.worker then
          game.perseason += 1
          game.money -= game.costs.worker
          game.costs.worker *= 1.05
          game.costs.worker = round(game.costs.worker)
          game.perseason = round(game.perseason)
        end
      end
    end
    if game.largestsum >= 100000000000 then
      if currentsong.getDuration() != 12.826083 then
        currentsong.stop()
      end
      currentsong = audio.playMusic( "theworldisending", 0.25 )
    elsif game.largestsum >= 100000000 then
      if currentsong.getDuration() != 16.039167 then
        currentsong.stop()
      end
      currentsong = audio.playMusic( "almostharvesttime", 0.25 )
    elsif game.largestsum >=1000000 then
      if currentsong.getDuration() != 19.226083 then
        currentsong.stop()
      end
      currentsong = audio.playMusic( "multitreelionaire", 0.25 )
    elsif game.largestsum >= 10000 then
      if currentsong.getDuration() != 15.986958 then
        currentsong.stop()
      end
      currentsong = audio.playMusic( "thegreatbigorchard", 0.25 )
    else
      if round(currentsong.getDuration()) != 36 then
        currentsong.stop()
      end
      currentsong = audio.playMusic( "moneygrowsontrees", 0.25 )
    end
  elsif gamestate == 0 then
    currentsong.stop()
    if checkRectMouseHover(0,-50, 70, 10) and mouse.press then
      gamestate = 1
    end
    if checkRectMouseHover(0,-70, 70, 10) and mouse.press then
      system.file.load( ["txt"] )
    end
  end
  game.perclick = round(game.perclick)
  game.money = round(game.money)
  if game.money > game.largestsum then
    game.largestsum = game.money
  end
  if system.file.loaded then
    for file in system.file.loaded
      corruptsave = 0
      jsontoparse = base64.decode(file.content)
      system.javascript("this.decodedgame = JSON.parse(player.runtime.vm.context.global.jsontoparse)")
      game = decodedgame
      gamestate = 1
    end
  end
end

draw = function()
  screen.setFont("playfairdisplaysemibold")
  screen.clear()
  if screen.isFontReady( "playfairdisplaysemibold" ) then
    if gamestate == 0 then
      if titleframe < 30 then titleframe += 0.2 else titleframe = 0 end
      if titleframe < 10 then
        screen.drawSprite("000"+floor(titleframe)+"min", 0, 0, screen.width)
      else
        screen.drawSprite("00"+floor(titleframe)+"min", 0, 0, screen.width)
      end
      screen.setDrawAnchor(-1,0)
      // screen.drawText("Your Username: "+storage.get("username"), leftAlign + 5, 90, 5, "#222")
      screen.drawText("Money", -45, 20, 15, "#fff")
      screen.drawText("Tree", -45, 2.5, 15, "#fff")
      screen.drawText("Simulator", -45, -15, 15, "#fff")
      screen.drawText("2023", 5, -30, 15, "#fff")
      screen.setDrawAnchor(0,0)
      screen.drawText("New Game", 0, -50, 10, "#fff")
      screen.drawText("Load Game", 0, -70, 10, "#fff")
    elsif gamestate == 1 then
      screen.drawSprite("background"+seasons[game.season], 0, 0, screen.width)
      for i = 1 to game.trees
        if game.trees  < 5 then
          screen.drawSprite( "tree"+seasons[game.season], ((i-1)*60 - (game.trees-1)*30)/(game.trees*.2), 0, 200)
        else
          screen.drawSprite( "tree"+seasons[game.season], ((i-1)*60 - (game.trees-1)*30)/(game.trees*.2), 0, 200/(game.trees*.2))
        end
        if moneytime == 1 then
          if game.trees  < 5 then
            screen.drawSprite( "dollaroverlay", ((i-1)*60 - (game.trees-1)*30)/(game.trees*.2), 0, 200)
          else
            screen.drawSprite( "dollaroverlay", ((i-1)*60 - (game.trees-1)*30)/(game.trees*.2), 0, 200/(game.trees*.2))
          end
        end
      end
      if moneybugattack == 1 then
        screen.drawSprite( "hit", 0, 0, screen.width, screen.height )
        screen.drawSprite( "moneybug", 0, 40, 120, 70 )
        screen.drawText("Moneybug Attack!", 0, -20, 10, "#fff")
      end
      screen.setDrawAnchor(-1, 0)
      screen.drawText(game.year, leftAlign + 10, 0, 20, "#fff")
      screen.drawText(seasons[game.season], leftAlign + 10, -20, 7, "#fff")
      screen.setDrawAnchor(1, 0)
      if game.trees == 1 then
        screen.drawText(game.trees +" tree", rightAlign-10, -60, 7, "#fff")
      else
        screen.drawText(game.trees +" trees", rightAlign-10, -60, 7, "#fff")
      end
      if game.repellant == 1 then
        screen.drawText(game.repellant+" bottle of repellant", rightAlign-10, -75, 7, "#fff")
      else
        screen.drawText(game.repellant+" bottles of repellant", rightAlign-10, -75, 7, "#fff")
      end
      if game.perseason == 1 then
        screen.drawText(game.perseason +" worker", rightAlign-10, -90, 7, "#fff")
      else
        screen.drawText(game.perseason +" workers", rightAlign-10, -90, 7, "#fff")
      end
      screen.setDrawAnchor(0, 0)
      if moneytime == 1 then
        screen.fillRoundRect(0,-80,100,30,4,"#52f")
        screen.drawText("Harvest", 0, -80, 10, "#fff")
      else
        screen.fillRoundRect(0,-80,100,30,4,"#115")
        screen.drawText("Harvest", 0, -80, 10, "#555")
      end
      screen.setDrawAnchor(-1,0)
      //screen.fillRoundRect(leftAlign+10,-80,230,60,4,"#fff")
      game.moneystring = "" + game.money
      screen.drawText("$"+game.display.money, leftAlign+10, -70, 20, "#fff")
      screen.drawText("$"+moneyRound(game.perclick)+" per tree", leftAlign+10, -90, 8, "#fff")
      screen.setDrawAnchor(0, 0)
      if shopopen == 1 then
        screen.fillRoundRect(rightAlign - 60, 25, 100, 100, 4, "#efeffa")
        if game.money >= game.costs.tree then
          screen.setColor("#222")
        else
          screen.setColor("#2226")
        end
        screen.drawText("New Money Tree - $"+game.display.tree, rightAlign - 60, 50, 5)
        if game.money >= game.costs.repellant then
          screen.setColor("#222")
        else
          screen.setColor("#2226")
        end
        screen.drawText("Moneybug Repellant - $"+game.display.repellant, rightAlign - 60, 30, 5)
        if game.money >= game.costs.fertilizer then
          screen.setColor("#222")
        else
          screen.setColor("#2226")
        end
        screen.drawText("Fertilizer - $"+game.display.fertilizer, rightAlign - 60, 10, 5)
        if game.money >= game.costs.worker then
          screen.setColor("#222")
        else
          screen.setColor("#2226")
        end
        screen.drawText("Hire Field Worker - $"+game.display.worker, rightAlign - 60, -10, 5)
      end
      screen.fillRoundRect(leftAlign + 40, 80, 70, 30, 4, "#fff")
      screen.drawText("Save", leftAlign + 47, 79, 10, "#222")
      screen.drawSprite( "save_icon", leftAlign + 20, 80, 16, 16 )
      screen.fillRoundRect(rightAlign - 60, 80, 100, 30, 4, "#fff")
      screen.drawText("Shop", rightAlign - 60, 80, 10, "#222")
      if help == 1 then
        screen.fillRect(0,0,screen.width,screen.height,"#0006")
        screen.fillRoundRect(0,-15,200,150,4,"#fff")
        screen.drawText("How to Play",0,45,8,"#222")
        text = [
          "Money Tree Simulator is all about making as much money as"
          "possible! To start, wait for the Harvest button to light up, and"
          "click it or press the spacebar to harvest the money. Now, click"
          "the shop to open it and purchase a New Money Tree. That's it!"
          "Other info:",
          "Moneybug Repellant - prevents loss of trees and money in raids",
          "Fertilizer - increases amount of money produced by each tree",
          "Workers - makes money per tree every season"
          "Tip: You can press the first letter of any option on the shop"
          "menu as a hotkey. It can be much faster than clicking!"
          ""
          "Click the Help button again to exit."
        ]
        for i = 0 to text.length - 1
          screen.drawText(text[i],0,30-(i*10),5,"#222")
        end
      end
      screen.fillRoundRect(leftAlign + 110, 80, 60, 30, 4,"#fff")
      screen.drawText("Help", leftAlign + 110, 80, 10, "#222")
    end
    if transition.active != 0 then
      screen.setAlpha(transition.alpha)
      screen.fillRect(0,0,screen.width, screen.height, transition.color)
      screen.setAlpha(1)
    end
  else
    screen.drawText("Loading Money Tree Simulator 2023....",0,0,10,"#fff")
  end
end