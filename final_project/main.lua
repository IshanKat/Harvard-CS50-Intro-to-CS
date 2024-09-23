-- Recreation of Tetris, originally made by Alexey Pajitnov
-- Author: Ishan Katpally

BASE_DIM = 20
blockDrawSize = BASE_DIM - 1

push = require 'push'

math.randomseed(os.time())

function love.load()
    xOffset = 5
    yOffset = 2
    love.window.setTitle('Tetris')
    love.graphics.setDefaultFilter('nearest', 'nearest')
    push:setupScreen(400, 440, 400, 440, {
        fullscreen = false, 
        resizable = true, 
        vsync = true
    })
    love.graphics.setBackgroundColor(1, 1, 1)
    smallFont = love.graphics.newFont('font.ttf', 20)
    largeFont = love.graphics.newFont('font.ttf', 70)

    pieces = {
        {
            {
                {' ', ' ', ' ', ' '},
                {'i', 'i', 'i', 'i'},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', ' ', 'i', ' '},
                {' ', ' ', 'i', ' '},
                {' ', ' ', 'i', ' '},
                {' ', ' ', 'i', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {' ', 'o', 'o', ' '},
                {' ', 'o', 'o', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {'j', 'j', 'j', ' '},
                {' ', ' ', 'j', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 'j', ' ', ' '},
                {' ', 'j', ' ', ' '},
                {'j', 'j', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {'j', ' ', ' ', ' '},
                {'j', 'j', 'j', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 'j', 'j', ' '},
                {' ', 'j', ' ', ' '},
                {' ', 'j', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {'l', 'l', 'l', ' '},
                {'l', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 'l', ' ', ' '},
                {' ', 'l', ' ', ' '},
                {' ', 'l', 'l', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', ' ', 'l', ' '},
                {'l', 'l', 'l', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {'l', 'l', ' ', ' '},
                {' ', 'l', ' ', ' '},
                {' ', 'l', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {'t', 't', 't', ' '},
                {' ', 't', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 't', ' ', ' '},
                {' ', 't', 't', ' '},
                {' ', 't', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 't', ' ', ' '},
                {'t', 't', 't', ' '},
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 't', ' ', ' '},
                {'t', 't', ' ', ' '},
                {' ', 't', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {' ', 's', 's', ' '},
                {'s', 's', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {'s', ' ', ' ', ' '},
                {'s', 's', ' ', ' '},
                {' ', 's', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
        {
            {
                {' ', ' ', ' ', ' '},
                {'z', 'z', ' ', ' '},
                {' ', 'z', 'z', ' '},
                {' ', ' ', ' ', ' '},
            },
            {
                {' ', 'z', ' ', ' '},
                {'z', 'z', ' ', ' '},
                {'z', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
            },
        },
    }
    createOrder()
    newPiece()
    gameState = 'start'
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.keypressed(key)
    if key == 'escape' then
        love.event.quit()
    end

    -- # denotes the length of something
    if gameState == 'play' then
        if key == 's' then
            local tmpRotation = pieceRotation + 1
            if tmpRotation > #pieces[pieceType] then
                tmpRotation = 1
            end

            if canMove(pieceX, pieceY, tmpRotation) then
                pieceRotation = tmpRotation
            end
        elseif key == 'w' then
            local tmpRotation = pieceRotation - 1
            if tmpRotation < 1 then
                tmpRotation = #pieces[pieceType]
            end

            if canMove(pieceX, pieceY, tmpRotation) then
                pieceRotation = tmpRotation
            end
        elseif key == 'left' then
            local tmpX = pieceX - 1
            if canMove(tmpX, pieceY, pieceRotation) then
                pieceX = tmpX
            end
        elseif key == 'right' then
            tmpX = pieceX + 1
            if canMove(tmpX, pieceY, pieceRotation) then
                pieceX = tmpX
            end
        elseif key == 'space' then
            while canMove(pieceX, pieceY + 1, pieceRotation) do
                pieceY = pieceY + 1
                score = score + 2
                timer = speed
            end
        elseif key == 'down' then
            if canMove(pieceX, pieceY + 1, pieceRotation) then
                pieceY = pieceY + 1
                score = score + 1
            end
        end
    end
    
    if gameState == 'end' or gameState == 'start' then
        if key == 'enter' or key == 'return' then
            reset()
        end
    end

end

function love.update(dt)
    if gameState == 'play' then
        timer = timer + dt
        if timer >= speed then
            timer = 0
            local tmpY = pieceY + 1
            if canMove(pieceX, tmpY, pieceRotation) then
                pieceY = tmpY
            else
                if pieceY == 0 then
                    gameState = 'end'
                else
                    for y = 1, tiles do
                        for x = 1, tiles do
                            local block = pieces[pieceType][pieceRotation][y][x]
                            if block ~= ' ' then
                                inert[pieceY + y][pieceX + x] = block
                            end
                        end
                    end
                    local lines_cleared = 0
                    for y = 1, yCount do
                        local complete_row = true
                        for x = 1, xCount do
                            if inert[y][x] == ' ' then
                                complete_row = false
                            end
                        end
                        if complete_row then
                            lines = lines + 1
                            lines_cleared = lines_cleared + 1
                            if lines >= 10 * level then
                                level = level + 1
                                speed = 1 - level * 4 / 100
                            end 
                            for removeY = y, 2, -1 do
                                for removeX = 1, xCount do
                                    inert[removeY][removeX] = inert[removeY - 1][removeX]
                                end
                            end
                        
                            for removeX = 1, xCount do
                                inert[1][removeX] = ' '
                            end
                        end
                    end
                    if lines_cleared == 1 then
                        score = score + 100 * level
                    elseif lines_cleared == 2 then
                        score = score + 300 * level
                    elseif lines_cleared == 3 then
                        score = score + 500 * level
                    elseif lines_cleared == 4 then
                        score = score + 800 * level
                    end
                end
                newPiece()
            end
        end
    end
end

function love.draw()

    push:apply('start')

    love.graphics.clear(0/255, 0/255, 0/255)
    if gameState == 'play' then
        
        local function drawBlock(block, x, y)
            local colors = {
                [' '] = {0.15, 0.15, 0.15},
                i = {.47, .76, .94},
                j = {0.1, 0.1, 1},
                l = {1, 168/255, 5/255},
                o = {1, 1, 0.1},
                s = {1, 0.1, 0.1},
                t = {1, 0.1, 1},
                z = {0, 1, 0},
                preview = {191/255, 191/255, 191/255}
            }
            local color = colors[block]
            love.graphics.setColor(color)
            love.graphics.rectangle(
                'fill',
                (x - 1 + xOffset) * BASE_DIM,
                (y - 1 + yOffset) * BASE_DIM,
                blockDrawSize,
                blockDrawSize
            )
        end

        for y = 1, yCount do
            for x = 1, xCount do
                drawBlock(inert[y][x], x, y)
            end
        end

        for y = 1, tiles do
            for x = 1, tiles do
                local block = pieces[pieceType][pieceRotation][y][x]
                if block ~= ' ' then
                    drawBlock(block, x + pieceX, y + pieceY)
                end
            end
        end

        for y = 1, tiles do
            for x = 1, tiles do
                local block = pieces[order[#order]][1][y][x]
                if block ~= ' ' then
                    if block == 'i' or block == 'o' then
                        drawBlock('preview', x - 4.5, y + 1)
                    else
                        drawBlock('preview', x - 4, y + 1)
                    end
                end
            end
        end
        love.graphics.setColor(1, 1, 1, 1)
        love.graphics.setFont(smallFont)
        love.graphics.print('NEXT', 28, 40)
        love.graphics.print('LINES: ' .. tostring(lines), 160, 15)
        love.graphics.print('LEVEL: ' .. tostring(level), 305, 280)
        love.graphics.print('SCORE', 320, 100)
        love.graphics.print(tostring(score), 310, 120)
    elseif gameState == 'end' then
        love.graphics.setFont(largeFont)
        love.graphics.setColor(1, 1, 1, 1)
        love.graphics.printf('GAME OVER',  5, 100, 400, 'center')
        love.graphics.setFont(smallFont)
        love.graphics.printf('Score: ' .. tostring(score), 0, 200, 400, 'center')
        love.graphics.printf('Press Enter to play again!', 0, 250, 400, 'center')
    elseif gameState == 'start' then
        love.graphics.setFont(largeFont)
        love.graphics.printf('Tetris', 0, 50, 400, 'center')
        love.graphics.setFont(smallFont)
        love.graphics.printf('Press Enter to start!', 0, 150, 400, 'center')
    end

    push:apply('end')
end

function canMove(tmpX, tmpY, tmpRotation)
    for x = 1, tiles do
        for y = 1, tiles do
            if pieces[pieceType][tmpRotation][y][x] ~= ' ' and (
                (tmpX + x) < 1 
                or tmpX + x > xCount 
                or tmpY + y > yCount
                or inert[tmpY + y][tmpX + x] ~= ' '
            )
                then
                return false
            end
        end
    end
    return true
end

function newPiece()
    pieceType = table.remove(order)
    pieceRotation = 1
    pieceX = 3
    pieceY = 0

    if #order == 0 then
        createOrder()
    end
end

function createOrder()
    order = {}
    for i = 1, #pieces do
        local position = love.math.random(#order + 1)
        table.insert(order, position, i)
    end
end

function reset()
    inert = {}
    xCount = 10
    yCount = 18
    for y = 1, yCount do
        inert[y] = {}
        for x = 1, xCount do
            inert[y][x] = ' '
        end
    end
    lines = 0
    score = 0
    level = 69
    speed = 1 - level * 4 / 100
    timer = 0
    tiles = 4
    gameState = 'play'
end