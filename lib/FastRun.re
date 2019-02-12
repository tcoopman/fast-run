open Revery.UI;
open Revery.Core;
open Revery.UI.Components;

let containerStyle =
  Style.[
    position(`Absolute),
    top(0),
    bottom(0),
    left(0),
    right(0),
    alignItems(`Center),
    justifyContent(`Center),
    flexDirection(`Column),
    backgroundColor(Colors.white),
  ];

module Example = {
  type inputFields = {first: string};

  let component = React.component("Example");

  let createElement = (~window, ~children as _, ()) =>
    component(slots => {
      let ({first}, setValue, slots) =
        React.Hooks.state({first: ""}, slots);

      (slots, <View style=containerStyle>
        <Input
          style=Style.[
            width(800),
            color(Colors.black),
            backgroundColor(Colors.paleVioletRed),
            fontSize(80),
            margin(20),
          ]
          window
          placeholder="Insert text here!!"
          placeholderColor=Colors.white
          onChange={(~value) => setValue({first: value})}
        />
      </View>);
    });
};

let render = (window) => <Example window />;
