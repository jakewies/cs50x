<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("buy_form.php", ["title" => "Buy Stock"]);
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol and shares
        if (empty($_POST["symbol"]))
        {
            apologize("Please provide a symbol.");
        }
        else if(empty($_POST["shares"]))
        {
            apologize("Please provide a valid share amount.");
        }
        // ensure valid stock
        $_POST["symbol"] = strtoupper($_POST["symbol"]);
        $stock = lookup($_POST["symbol"]);
        if ($stock !== false)
        {
            // set transaction type for history
            $transaction = "BUY";

            // check for whole shares
            if (!preg_match("/^\d+$/", $_POST["shares"]))
            {
                apologize("Please provide a valid share amount");
            }

            // ensure user has appropriate funds to buy stock
            $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            $user_cash = $user[0]["cash"];
            $price = number_format($stock["price"], 2, ".", ",");

            $stock_price = $price * $_POST["shares"];

            if ($user_cash > $stock_price)
            {
                // update user's portfolio with new stock
                query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + ?", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $_POST["shares"]);

                // update user's cash
                query("UPDATE users SET cash = cash - ? WHERE id = ?", $stock_price, $_SESSION["id"]);

                // update user's history
                query("INSERT INTO history (id, transaction, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?, NOW())",
                $_SESSION["id"], $transaction, $_POST["symbol"], $_POST["shares"], $price);

                // redirect user to portfolio
                redirect("/");
            }
            else
            {
                apologize("Insufficient funds.");
            }
        }
        else
        {
            apologize("Invalid symbol.");
        }
    }
?>
