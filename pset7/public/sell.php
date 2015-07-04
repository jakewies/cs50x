<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // add symbols to form
        $rows = query("SELECT symbol FROM portfolio WHERE id = ?", $_SESSION["id"]);

        // define array to hold symbols
        $symbols = [];

        foreach ($rows as $row)
        {
            $symbols[] = $row["symbol"];
        }

        // render form
        render("sell_form.php", ["title" => "Sell Stock", "symbols" => $symbols]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol
        if (empty($_POST["symbol"]))
        {
            apologize("Please choose a stock to sell.");
        }

        // set transaction type for history
        $transaction = "SELL";

        // get user's # of shares of stock
        $shares = query("SELECT shares FROM portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], $_POST["symbol"]);

        // look up stock's latest price
        $stock = lookup($_POST["symbol"]);

        // format price
        $price = number_format($stock["price"], 2, ".", ",");

        $proceeds = $shares[0]["shares"] * $price;

        // delete stock from user's portfolio
        query("DELETE FROM portfolio WHERE id = ? and symbol = ?", $_SESSION["id"], $_POST["symbol"]);

        // update user's cash
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $proceeds, $_SESSION["id"]);

        // update user's history
        query("INSERT INTO history (id, transaction, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?, NOW())",
        $_SESSION["id"], $transaction, $_POST["symbol"], $shares[0]["shares"], $price);

        // redirect to portfolio
        redirect("/");
    }
?>
