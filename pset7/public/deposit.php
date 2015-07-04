<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit_form.php", ["title" => "Deposit Funds"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate button was checked
        if (isset($_POST["deposit"]))
        {
            $deposit = $_POST["deposit"];

            // update user's cash
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $deposit, $_SESSION["id"]);

            // redirect user to portfolio
            redirect("/");
        }
        else
        {
            apologize("Please enter a valid amount to be deposited.");
        }
    }
?>
