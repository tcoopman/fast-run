open Revery;
open Revery.Core;
open Revery.UI;
open Revery.UI.Components;

type state = int;

let state = 0;

let noop = () => ();

type action =
  | NoOp;

let reducer = (s: state, a: action) => {
  switch (a) {
  | NoOp => s
  };
};

let init = app => {
  let maximized = Environment.webGL;

  let dimensions: Monitor.size =
    Monitor.getPrimaryMonitor() |> Monitor.getSize;

  let windowWidth = dimensions.width / 2;
  let windowHeight = dimensions.height / 2;

  let win =
    App.createWindow(
      app,
      "FastRun!",
      ~createOptions={
        ...Window.defaultCreateOptions,
        width: windowWidth,
        height: windowHeight,
        maximized,
      },
    );

  let render = () => {
    Lib.FastRun.render();
  };

  let xPosition = (dimensions.width - windowWidth) / 2;
  let yPosition = (dimensions.height - windowHeight) / 2;
  Window.setPos(win, xPosition, yPosition);

  UI.start(win, render);
};

App.startWithState(state, reducer, init);

let () = {
  Lwt_main.run(
    {
      let%lwt line =
        Lwt_process.pread(("rg", [|"rg", "--files", "--max-depth=1"|]));
      Lwt_io.write(Lwt_io.stdout, Printf.sprintf("l: %s", line));
      Lwt_io.write(Lwt_io.stdout, Printf.sprintf("end"));
      /* List.map(line => Lwt_io.write(Lwt_io.stdout, Printf.sprintf("l: %s", line)), lines) */
    },
  );
};
