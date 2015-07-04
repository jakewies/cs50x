<?php

    // configuration
    require("../includes/config.php");

    // query user's portfolio
    $rows =	query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);

    // define array to be passed to portfolio
    $positions = [];

    // iterate through queried rows
    foreach ($rows as $row)
    {
        // lookup current value of stock
        $stock = lookup($row["symbol"]);

        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"], 2, ".", ","),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }

    // query user's cash
    $user_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $user_cash, "title" => "Portfolio"]);
?>
