<table id="history" class= "table table-striped">
    <thead>
        <th>Transaction</th>
        <th>Date/Time</th>
        <th>Symbol</th>
        <th>Shares</th>
        <th>Price</th>
    </thead>
    <tbody>
        <?php foreach ($history as $transaction): ?>
            <tr>
                <td><?= $transaction["transaction"] ?></td>
                <td><?= $transaction["date"] ?></td>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td>$<?= $transaction["price"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>
