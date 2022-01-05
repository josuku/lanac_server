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
                    @if (empty($picture['error']))
                        <td><a target="_blank" href="./api/picture/processed/{{ $picture['id'] }}">Image</a></td>
                    @else
                    <td><a href="#" data-toggle="popover" title="Error" data-content="{{ $picture['error'] }}">Error</a></td>
                    @endif
                </tr>
            @endforeach
            </tbody>
        </table>

        <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
        <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
        <script>
            $(document).ready(function(){
                $('[data-toggle="popover"]').popover();   
            });
        </script>
    </body>
</html>
