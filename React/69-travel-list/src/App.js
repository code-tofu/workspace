// import "./App.css"; //index.css is the global level css

const initialItems = [
  { id: 1, description: "Passport", quantity: 1, packed: false },
  { id: 2, description: "Phone", quantity: 1, packed: false },
  { id: 3, description: "Wallet", quantity: 1, packed: true },
];

export default function App() {
  return (
    <div className="app">
      <Logo />
      <Form />
      <PackingList />
      <Stats />
    </div>
  );
}

function Logo() {
  return <h1>Far Away Packing List App</h1>;
}

function Form() {
  function handleSubmit(e) {
    e.preventDefault();
    // <onsubmit="return false">
    console.log("Submitted", e);
  }
  return (
    <form className="add-form" onSubmit={handleSubmit}>
      <h3>What do you need for your trip?</h3>

      {/* method 1 */}
      <select>
        {Array.from({ length: 10 }, (_, i) => (
          <option value={i + 1} key={i + 1}>
            1:{i + 1}
          </option>
        ))}
      </select>

      {/* method 2 */}
      <select>
        {Array.from({ length: 20 }, (_, i) => i + 1).map((num) => (
          <option value={num} key={num}>
            2:{num}
          </option>
        ))}
      </select>

      <input type="text" placeholder="Item Name"></input>
      <button type="submit"> Add </button>
    </form>
  );
}
function PackingList() {
  return (
    <div className="list">
      <ul>
        {initialItems.map((item) => (
          <Item item={item} key={item.id} />
        ))}
      </ul>
    </div>
  );
}

function Item({ item }) {
  return (
    <li>
      <span style={item.packed ? { textDecoration: "line-through" } : {}}>
        {item.quantity} {item.description}
        {!item.packed ? (
          <button>
            <h2>X</h2>
          </button>
        ) : (
          <span></span>
          // <></> is a React Fragment
        )}
      </span>
    </li>
  );
}
function Stats() {
  return (
    <footer className="stats">
      <em>
        You have X items in your list, and you have already packed Y items. (Z%
        done)
      </em>
    </footer>
  );
}
