<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol
        if (empty($_POST["symbol"]))
        {
            apologize("Please provide a symbol.");
        }


        // look up stock's latest price
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        $stock = lookup($_POST["symbol"]);
        
        if ($stock !== false)
        {
            // format price
            $price = number_format($stock["price"], 2, ".", ",");

            // render quote
            render("quote_display.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $price]);
        }
        else
        {
            apologize("Invalid symbol.");
        }
    }
