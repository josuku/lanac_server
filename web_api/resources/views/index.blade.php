<html>
    <head>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
    </head>
    <body>
        <h1>Client-Server Generated Data </h1>

        <table class="table">
            <thead>
                <tr>
                    <th scope="col">Id</th>
                    <th scope="col">Name</th>
                    <th scope="col">Operation</th>
                    <th scope="col">Created At</th>
                    <th scope="col">IpAddress</th>
                    <th scope="col">Original</th>
                    <th scope="col">Processed</th>
                </tr>
            </thead>
            <tbody>
            @foreach($pictures as $picture)
                <tr>
                    <td>{{ $picture['id'] }}</td>
                    <td>{{ $picture['filename'] }}</td>
                    <td><?php if ($picture['operation'] == 1) echo "Rotate Left"; else echo "Rotate Right"; ?></td>
                    <td>{{ $picture['created_at'] }}</td>
                    <td>{{ $picture['ip_address'] }}</td>
                    <td><a target="_blank" href="./api/picture/original/{{ $picture['id'] }}">Image</a></td>
                    <td><a target="_blank" href="./api/picture/processed/{{ $picture['id'] }}">Image</a></td>
                </tr>
            @endforeach
            </tbody>
    </body>
</html>
