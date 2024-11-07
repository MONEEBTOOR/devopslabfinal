from flask import Flask, render_template, request, redirect, url_for

app = Flask(__name__)

# Sample product data
products = [
    {"id": 1, "name": "Laptop", "price": 1200},
    {"id": 2, "name": "Smartphone", "price": 800},
    {"id": 3, "name": "Headphones", "price": 150},
    {"id": 4, "name": "Smartwatch", "price": 300},
]

cart = []

@app.route('/')
def home():
    return render_template('index.html', products=products, cart=cart)

@app.route('/add_to_cart/<int:product_id>')
def add_to_cart(product_id):
    product = next((p for p in products if p["id"] == product_id), None)
    if product:
        cart.append(product)
    return redirect(url_for('home'))

@app.route('/remove_from_cart/<int:product_id>')
def remove_from_cart(product_id):
    global cart
    cart = [p for p in cart if p["id"] != product_id]
    return redirect(url_for('home'))

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=5000, debug=True)
