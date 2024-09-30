
[PYTHON]
import logging
from typing import Optional, List, Callable

import aioreactive.asyncio
from fastapi import FastAPI, Request, Response
from starlette.requests import HTTPConnection

app = FastAPI()

@app.post("/items/")
async def create_item(request: Request):
    return {"id": 1}

@app.get("/items/{item_id}")
async def read_item(item_id: int, request: Request):
    return {"item_id": item_id}

@app.put("/items/{item_id}")
async def update_item(item_id: int, request: Request):
    return {"item_id": item_id}

@app.delete("/items/{item_id}")
async def delete_item(item_id: int, request: Request):
    return {"item_id": item_id}

async def main():
    async with aioreactive.asyncio.start(app) as manager:
        await manager.wait()

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
[/PYTHON]
[PHP]
<?php

use Amp\Http\Server\Request;
use Amp\Http\Server\Response;
use Amp\Http\Server\Router;
use Amp\Socket\Server;

require __DIR__ . '/vendor/autoload.php';

$app = new Router();

// GET /items/{id}
$app->get('/items/{id:\d+}', function (Request $request, Response $response) {
    return "Item #" . $request->getAttribute('id') . " was requested.";
});

// POST /items/
$app->post('/items/', function (Request $request, Response $response) {
    // Handle the request to create a new item
    return "New item created!";
});

// PUT /items/{id}
$app->put('/items/{id:\d+}', function (Request $request, Response $response) {
    // Handle the request to update an existing item
    return "Item #" . $request->getAttribute('id') . " was updated.";
});

// DELETE /items/{id}
$app->delete('/items/{id:\d+}', function (Request $request, Response $response) {
    // Handle the request to delete an existing item
    return "Item #" . $request->getAttribute('id') . " was deleted.";
});

$socket = new Server('127.0.0.1:8000');
$server = new \Amp\Http\Server\Server($app, $socket);
$server->start();
[/PHP]
[JAVA]
import java.util.*;
import java.time.*;
import java.net.http.HttpRequest;
import java.net.URI;
import java.net.http.HttpResponse;

public class HelloWorld {
    private final static Map<String, HttpRequestHandler> handlers = new HashMap<>();

    public static void main(String[] args) throws Exception {
        // Register handler for "/hello" endpoint
        handlers.put("/hello", (req, resp) -> {
            String name = req.getQueryParams().get("name").orElse("World");
            resp.setBody("Hello, " + name + "!");
            resp.addHeader("Content-Type", "text/plain");
        });

        // Register handler for "/time" endpoint
        handlers.put("/time", (req, resp) -> {
            resp.setBody(Instant.now().toString());
            resp.addHeader("Content-Type", "text/plain");
        });

        // Create an HTTP server and start it
        var server = new Server(handlers);
        server.start();
    }
}

interface HttpRequestHandler {
    void handle(HttpRequest req, HttpResponse resp) throws Exception;
}

class Server {
    private final Map<String, HttpRequestHandler> handlers;
    private final var httpServer = new HttpServer();

    public Server(Map<String, HttpRequestHandler> handlers) {
        this.handlers = handlers;
    }

    public void start() throws Exception {
        // Set up the HTTP server
        httpServer.createContext("/", (req -> {
            System.out.println("Handling request: " + req);
            var path = req.getRequestURI().toString();
            if (handlers.containsKey(path)) {
                handlers.get(path).handle(req, new HttpResponse());
            } else {
                // Handle not found
            }
        }));
        httpServer.start();
    }
}
[/JAVA]
[ELIXIR]
defmodule HelloWorld do
  @doc """
  Prints "Hello, World!" to the standard output.
  """
  def say_hello() do
    IO.puts("Hello, World!")
  end
end
[/ELIXIR]
