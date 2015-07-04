<table id="portfolio" class="table table-striped">
    <tr>
        <th>Symbol</th>
        <th>Name</th>
        <th>Shares</th>
        <th>Price per Share</th>
        <th>TOTAL</th>
    </tr>

    <?php foreach ($positions as $position): ?>
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["name"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= $position["price"] ?></td>
            <td>$<?= number_format($position["price"] * $position["shares"], 2, ".", ",") ?></td>
        </tr>
    <?php endforeach ?>
    <tr id="cash">
        <td colspan="4"><strong>Cash</strong></td>
        <td><strong><?= number_format($cash[0]["cash"], 2, ".", ",")?></strong></td>
     </tr>
</table>
