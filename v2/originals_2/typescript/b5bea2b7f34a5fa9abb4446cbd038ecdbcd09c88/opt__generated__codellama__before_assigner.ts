const untracker = [undefined, null];

type BasicTypes = string | number | symbol | bigint | object | boolean | Function;
type Types = BasicTypes | BasicTypes[];
type TypesWithExclude = BasicTypes | undefined | null | TypesWithExclude[];

function Assigner(delegate: (a: any, b: any) => any, useuntrack: boolean = true): (...args: any[]) => any {
  return (...args: any[]): any => {
    console.log({ args });
    return args.reduce((a, b) => {
      if (!useuntrack && untracker.includes(b)) {
        throw new TypeError(`can't convert ${b} to object`);
      }
      Object.keys(b).forEach(key => {
        if (untracker.includes(a[key])) {
          a[key] = b[key];
        } else {
          a[key] = delegate.call(this, a[key], b[key]);
        }
      });
      return a;
    }, {});
  };
}

Assigner.count = (qty: number, delegate: (arg: any, ...args: any[]) => any) => {
  const assigner = (...receives: any[]): any => {
    let group = receives.shift();
    if (!useuntrack && untracker.includes(group)) {
      throw new TypeError(`can't convert ${group} to object`);
    }
    let args = receives.splice(0, qty - 1);
    while (args.length) {
      const keys = [];
      for (const arg of args) {
        for (const key of Object.keys(arg)) {
          if (!keys.includes(key)) {
            keys.push(key);
          }
        }
      }
      for (const key of keys) {
        group[key] = delegate.call(this, group[key], ...args.map(arg => arg[key]));
      }
      args = receives.splice(0, qty - 1);
    }
    return group;
  };
  return assigner;
}
