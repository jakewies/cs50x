<?php

    // configuration
    require("../includes/config.php");

    // query user's history
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);

    // define array to hold each transaction in user's history
    $history = [];

    // iterate through transactions
    foreach ($rows as $row)
    {
        $history[] = [
            "id" => $row["id"],
            "transaction" => $row["transaction"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => number_format($row["price"], 2, ".", ","),
            "date" => $row["date"]
        ];
    }

    // render history
    render("history_form.php", ["history" => $history, "title" => "Transaction History"]);
?>
